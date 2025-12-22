#!pip install -q torchsummary

import os

main_folder = './dataset/'

listdir = sorted(os.listdir(main_folder))

import numpy as np
import torch
from torch.utils.data import DataLoader, random_split
import torchvision
import torchvision.transforms as T
from torchvision.datasets import ImageFolder
from torchvision.utils import make_grid, save_image
import matplotlib.pyplot as plt

stats = ([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])
size = 224
batch_size=64
channels = 3

transformer = T.Compose([
    T.Resize(size), 
    T.CenterCrop(size),
    T.ToTensor(),
    T.Normalize(*stats)
])

dataset = ImageFolder(main_folder, transform=transformer)
classes = dataset.classes

len(dataset), dataset[0][0].size()





def denormal(image):
    image = image.numpy().transpose(1, 2, 0)
    mean = [0.485, 0.456, 0.406]
    std = [0.229, 0.224, 0.225]
#     mean = (0.5,)
#     std = (0.5,)
    
    image = image * std + mean
    image = np.clip(image, 0, 1)
    return image

def denormalize(x, mean=stats[0], std=stats[1]):
    # 3, H, W, B
    ten = x.clone().permute(1, 2, 3, 0)
    for t, m, s in zip(ten, mean, std):
        t.mul_(s).add_(m)
    # B, 3, H, W
    return torch.clamp(ten, 0, 1).permute(3, 0, 1, 2)

idx =  -1#@param
img, lbl = dataset[idx]

plt.imshow(denormal(img))
plt.title(dataset.classes[lbl])
plt.axis('off');

torch.manual_seed(42)

num_val = int(len(dataset) * 0.1) #240416_1419_glory : 전체에서 10%를 평가용으로 사용한다.

dataset, val_ds = random_split(dataset, [len(dataset) - num_val, num_val]) #여기서 데이터셋 두개를 변경해서 작성하면 원하는 랜덤이 아닌 따로따로 입력이 가능할 것 같다.

dl = DataLoader(dataset, batch_size=batch_size, shuffle=True, pin_memory=True, num_workers=3)
val_dl = DataLoader(val_ds, batch_size=batch_size, shuffle=True, pin_memory=False, num_workers=3)

def show_batch(dl):
    for images, labels in dl:
        fig, ax = plt.subplots(figsize=(12, 12))
        ax.set_xticks([]); ax.set_yticks([])
        denorm_images = denormalize(images)
        ax.imshow(make_grid(denorm_images[:64], nrow=8).permute(1, 2, 0).clamp(0,1))
        break






device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
device

import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision.models as models
from torchsummary import summary
from glob import glob
from tqdm.notebook import tqdm





class Recog(nn.Module):
    def __init__(self, num_classes, pretrained=True):
        super().__init__()
        # Use a pretrained model
        self.resnet18 = models.resnet18(True)
        self.features = nn.Sequential(*list(self.resnet18.children())[:-1])
        # Replace last layer
        self.classifier = nn.Sequential(nn.Flatten(),
                                         nn.Linear(self.resnet18.fc.in_features, num_classes))

    def forward(self, x):
        x = self.features(x)
        y = self.classifier(x)
        return y
    
    def summary(self, input_size):
        return summary(self, input_size)
    

model = Recog(num_classes=len(classes)).to(device)
model.summary((3, 224, 224)) #240416_1357_glory : 여기 나중에 지우는거 검토해보자




learning_rate = 1e-4
n_epochs = 7

criterion = nn.CrossEntropyLoss()
optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)

def train(epoch, n_epochs, model, dl, loss_func, device, optimizer, ds=dataset):
    model.train(True)
    torch.set_grad_enabled(True)
    
    epoch_loss = 0.0
    epochs_acc = 0
    
    tq_batch = tqdm(dl, total=len(dl))
    for images, labels in tq_batch:
        images = images.to(device)
        labels = labels.to(device)
        
        optimizer.zero_grad()
        outs = model(images)
        _, preds = torch.max(outs, 1)
        
        loss = loss_func(outs, labels)

        loss.backward()
        optimizer.step()

        epoch_loss += loss.item()
        epochs_acc += torch.sum(preds == labels).item()
        
        tq_batch.set_description(f'Epoch [{epoch + 1}/{n_epochs}]')
        tq_batch.set_postfix_str('loss = {:.4f}'.format(loss.item()))


    epoch_loss = epoch_loss / len(dl)
    epochs_acc = epochs_acc / len(ds)

    return epoch_loss, epochs_acc

def evaluate(model, dl, loss_func, device, ds=val_ds):

    model.train(False)

    epoch_loss = 0
    epochs_acc = 0
    tq_batch = tqdm(dl, total=len(dl), leave=False)
    for images, labels in tq_batch:

        images = images.to(device)
        labels = labels.to(device)

        outputs = model(images)
        _, preds = torch.max(outputs, 1)
        loss = loss_func(outputs, labels)

        epoch_loss += loss.item()
        epochs_acc += torch.sum(preds == labels).item()
        tq_batch.set_description(f'Evaluate Model')
        
    epoch_loss = epoch_loss / len(dl)
    epochs_acc = epochs_acc / len(ds)

    return epoch_loss, epochs_acc

def fit(n_epochs, model, train_dataloader, valid_dataloader, loss_func, device, optimizer):
    
    history = []
    val_loss_ref = float('inf')
    patient = 2 #5
    for epoch in range(n_epochs):
        torch.cuda.empty_cache()
        loss, acc = train(epoch, n_epochs, model, train_dataloader, loss_func, device, optimizer)
        
        torch.cuda.empty_cache()
        val_loss, val_acc = evaluate(model, valid_dataloader, loss_func, device)
        
        history.append({'loss': loss, 'acc': acc, 'val_loss': val_loss, 'val_acc': val_acc})

        statement = "[loss]={:.4f} - [acc]={:.4f} - \
[val_loss]={:.4f} - [val_acc]={:.4f}".format(loss, acc, val_loss, val_acc,)
        print(statement)
        ####### Checkpoint
        if val_loss < val_loss_ref:
            patient = 2 #5
            val_loss_ref = val_loss
            model_path = './Recognition_checkpoint.pth'
            torch.save(model.state_dict(), model_path)
            print(f"[INFO] Saving model dict, Epoch={epoch + 1}")
        else:
            if patient == 0: 
                break
            print(f"[INFO] {patient} lives left!")
            patient -= 1
            

    return history






res = fit(n_epochs, model, dl, val_dl, criterion, device, optimizer)






def show_results(history):
    accuracy = [res['acc'] for res in history]
    losses = [res['loss'] for res in history]
    val_accuracy = [res['val_acc'] for res in history]
    val_losses = [res['val_loss'] for res in history]
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize = (10, 5))
    ax1.plot(losses, '-o', label = 'Loss')
    ax1.plot(val_losses, '-o', label = 'Validation Loss')
    ax1.legend()

    ax2.plot(100 * np.array(accuracy), '-o', label = 'Accuracy')
    ax2.plot(100 * np.array(val_accuracy), '-o', label = 'Validation Accuracy')
    ax2.legend();
    
    fig.show()

show_results(res) #240416_1357_glory : 이것도 안오신다.











y_test, y_pred = [], []
for imgs, lbls in tqdm(val_dl):
    imgs = imgs.to(device)
    outs = model(imgs)
    _, preds = torch.max(outs, dim = 1)
    y_test += lbls.tolist()
    y_pred += preds.tolist()
    
loss, acc = evaluate(model, val_dl, criterion, device)
print(f'loss: {loss} - acc: {acc}')

#from termcolor import colored


for i, name in enumerate(classes):
    name = name.split("_")[-1]
    classes[i] = name










idx = 16
for imgs, lbls in val_dl:
    imgs = imgs.to(device)
    outs = model(imgs)
    _, preds = torch.max(outs, dim = 1)
    fig, ax = plt.subplots(figsize=(12, 12))
    ax.set_xticks([]); ax.set_yticks([])
    denorm_images = denormalize(imgs.cpu())
    ax.imshow(make_grid(denorm_images[:idx], nrow=8).permute(1, 2, 0).clamp(0,1)) #240416_1358_glory : 이것도 나중에 지우는것 검토
    for p, lbl in zip(preds[:idx], lbls[:idx]):
        if lbl == p.cpu():
            print(classes[p]) #240416_1358_glory : 이것도 나중에 지우는것 검토
        else:
            print(classes[p], classes[lbl]) #240416_1358_glory : 이것도 나중에 지우는것 검토
    break






#!pip install seaborn








#module 'numpy' has no attribute '_no_nep50_warning' 오류 발생
#1트
#!pip install langchain
#!pip install sentence-transformers
#https://stackoverflow.com/questions/77064579/module-numpy-has-no-attribute-no-nep50-warning
#2트
#!pip install scikit-learn

from sklearn.metrics import confusion_matrix, classification_report
import pandas as pd
import seaborn as sns


cm = confusion_matrix(y_test, y_pred, normalize = 'true')
cm_df = pd.DataFrame(cm)
plt.figure(figsize=(50, 50))
plt.title('Confusion Matrix')
sns.heatmap(cm_df, annot=True, cmap='Blues', square=True);


print(classification_report(y_test, y_pred))


'''
#아래는 yaml파일 정보입니다.

name: lwir
channels:
  - pytorch3d
  - pytorch
  - iopath
  - nvidia
  - defaults
  - conda-forge
dependencies:
  - _libgcc_mutex=0.1=main
  - _openmp_mutex=5.1=1_gnu
  - alsa-lib=1.2.3.2=h166bdaf_0
  - blas=1.0=mkl
  - bzip2=1.0.8=h7b6447c_0
  - ca-certificates=2024.2.2=hbcca054_0
  - cairo=1.16.0=h6cf1ce9_1008
  - certifi=2024.2.2=pyhd8ed1ab_0
  - charset-normalizer=2.0.4=pyhd3eb1b0_0
  - colorama=0.4.6=pyhd8ed1ab_0
  - cuda=11.6.1=0
  - cuda-cccl=11.6.55=hf6102b2_0
  - cuda-command-line-tools=11.6.2=0
  - cuda-compiler=11.6.2=0
  - cuda-cudart=11.6.55=he381448_0
  - cuda-cudart-dev=11.6.55=h42ad0f4_0
  - cuda-cuobjdump=11.6.124=h2eeebcb_0
  - cuda-cupti=11.6.124=h86345e5_0
  - cuda-cuxxfilt=11.6.124=hecbf4f6_0
  - cuda-driver-dev=11.6.55=0
  - cuda-gdb=12.3.101=0
  - cuda-libraries=11.6.1=0
  - cuda-libraries-dev=11.6.1=0
  - cuda-memcheck=11.8.86=0
  - cuda-nsight=12.3.101=0
  - cuda-nsight-compute=12.3.2=0
  - cuda-nvcc=11.6.124=hbba6d2d_0
  - cuda-nvdisasm=12.3.101=0
  - cuda-nvml-dev=11.6.55=haa9ef22_0
  - cuda-nvprof=12.3.101=0
  - cuda-nvprune=11.6.124=he22ec0a_0
  - cuda-nvrtc=11.6.124=h020bade_0
  - cuda-nvrtc-dev=11.6.124=h249d397_0
  - cuda-nvtx=11.6.124=h0630a44_0
  - cuda-nvvp=12.3.101=0
  - cuda-runtime=11.6.1=0
  - cuda-samples=11.6.101=h8efea70_0
  - cuda-sanitizer-api=12.3.101=0
  - cuda-toolkit=11.6.1=0
  - cuda-tools=11.6.1=0
  - cuda-visual-tools=11.6.1=0
  - dbus=1.13.6=h48d8840_2
  - expat=2.4.8=h27087fc_0
  - ffmpeg=4.3.2=hca11adc_0
  - fontconfig=2.14.0=h8e229c2_0
  - freetype=2.12.1=h4a9f257_0
  - fvcore=0.1.5.post20221221=pyhd8ed1ab_0
  - gds-tools=1.8.1.2=0
  - gettext=0.19.8.1=h73d1719_1008
  - glib=2.68.4=h9c3ff4c_1
  - glib-tools=2.68.4=h9c3ff4c_1
  - gmp=6.2.1=h295c915_3
  - gnutls=3.6.15=he1e5248_0
  - graphite2=1.3.13=h58526e2_1001
  - gst-plugins-base=1.18.5=hf529b03_0
  - gstreamer=1.18.5=h76c114f_0
  - harfbuzz=2.9.1=h83ec7ef_1
  - hdf5=1.10.6=nompi_h3c11f04_101
  - icu=68.2=h9c3ff4c_0
  - idna=3.4=py39h06a4308_0
  - intel-openmp=2023.1.0=hdb19cb5_46306
  - iopath=0.1.9=py39
  - jasper=1.900.1=h07fcdf6_1006
  - jpeg=9e=h5eee18b_1
  - keyutils=1.6.1=h166bdaf_0
  - krb5=1.19.3=h3790be6_0
  - lame=3.100=h7b6447c_0
  - lcms2=2.12=h3be6417_0
  - ld_impl_linux-64=2.38=h1181459_1
  - lerc=3.0=h295c915_0
  - libblas=3.9.0=1_h6e990d7_netlib
  - libcblas=3.9.0=3_h893e4fe_netlib
  - libclang=11.1.0=default_ha53f305_1
  - libcublas=11.9.2.110=h5e84587_0
  - libcublas-dev=11.9.2.110=h5c901ab_0
  - libcufft=10.7.1.112=hf425ae0_0
  - libcufft-dev=10.7.1.112=ha5ce4c0_0
  - libcufile=1.8.1.2=0
  - libcufile-dev=1.8.1.2=0
  - libcurand=10.3.4.107=0
  - libcurand-dev=10.3.4.107=0
  - libcusolver=11.3.4.124=h33c3c4e_0
  - libcusparse=11.7.2.124=h7538f96_0
  - libcusparse-dev=11.7.2.124=hbbe9722_0
  - libdeflate=1.17=h5eee18b_1
  - libedit=3.1.20191231=he28a2e2_2
  - libevent=2.1.10=h9b69904_4
  - libffi=3.4.4=h6a678d5_0
  - libgcc-ng=11.2.0=h1234567_1
  - libgfortran-ng=7.5.0=h14aa051_20
  - libgfortran4=7.5.0=h14aa051_20
  - libglib=2.68.4=h174f98d_1
  - libgomp=11.2.0=h1234567_1
  - libiconv=1.16=h7f8727e_2
  - libidn2=2.3.4=h5eee18b_0
  - liblapack=3.9.0=3_h893e4fe_netlib
  - liblapacke=3.9.0=3_h893e4fe_netlib
  - libllvm11=11.1.0=hf817b99_2
  - libnpp=11.6.3.124=hd2722f0_0
  - libnpp-dev=11.6.3.124=h3c42840_0
  - libnvjpeg=11.6.2.124=hd473ad6_0
  - libnvjpeg-dev=11.6.2.124=hb5906b9_0
  - libogg=1.3.4=h7f98852_1
  - libopencv=4.5.2=py39h2406f9b_0
  - libopus=1.3.1=h7f98852_1
  - libpng=1.6.39=h5eee18b_0
  - libpq=13.3=hd57d9b9_0
  - libprotobuf=3.15.8=h780b84a_1
  - libstdcxx-ng=11.2.0=h1234567_1
  - libtasn1=4.19.0=h5eee18b_0
  - libtiff=4.2.0=hf544144_3
  - libunistring=0.9.10=h27cfd23_0
  - libuuid=2.32.1=h7f98852_1000
  - libvorbis=1.3.7=h9c3ff4c_0
  - libwebp-base=1.3.2=h5eee18b_0
  - libxcb=1.13=h7f98852_1004
  - libxkbcommon=1.0.3=he3ba5ed_0
  - libxml2=2.9.12=h72842e0_0
  - lz4-c=1.9.4=h6a678d5_0
  - mkl=2023.1.0=h213fc3f_46344
  - mkl-service=2.4.0=py39h5eee18b_1
  - mkl_fft=1.3.8=py39h5eee18b_0
  - mkl_random=1.2.4=py39hdb19cb5_0
  - mysql-common=8.0.25=ha770c72_2
  - mysql-libs=8.0.25=hfa10184_2
  - ncurses=6.4=h6a678d5_0
  - nettle=3.7.3=hbbd107a_1
  - nsight-compute=2023.3.1.1=0
  - nspr=4.32=h9c3ff4c_1
  - nss=3.69=hb5efdd6_1
  - opencv=4.5.2=py39hf3d152e_0
  - openh264=2.1.1=h4ff587b_0
  - openjpeg=2.4.0=h3ad879b_0
  - openssl=1.1.1o=h166bdaf_0
  - pcre=8.45=h9c3ff4c_0
  - pillow=10.2.0=py39h5eee18b_0
  - pip=23.3.1=py39h06a4308_0
  - pixman=0.40.0=h36c2ea0_0
  - portalocker=2.8.2=py39hf3d152e_1
  - pthread-stubs=0.4=h36c2ea0_1001
  - py-opencv=4.5.2=py39hef51801_0
  - python=3.9.7=hb7a2778_3_cpython
  - python_abi=3.9=2_cp39
  - pytorch=1.13.0=py3.9_cuda11.6_cudnn8.3.2_0
  - pytorch-cuda=11.6=h867d48c_1
  - pytorch-mutex=1.0=cuda
  - pytorch3d=0.7.5=py39_cu116_pyt1130
  - pyyaml=6.0=py39hb9d737c_4
  - qt=5.12.9=hda022c4_4
  - readline=8.2=h5eee18b_0
  - requests=2.31.0=py39h06a4308_1
  - setuptools=68.2.2=py39h06a4308_0
  - sqlite=3.41.2=h5eee18b_0
  - tabulate=0.9.0=pyhd8ed1ab_1
  - tbb=2021.8.0=hdb19cb5_0
  - termcolor=2.4.0=pyhd8ed1ab_0
  - tk=8.6.12=h1ccaba5_0
  - torchvision=0.14.0=py39_cu116
  - tqdm=4.66.2=pyhd8ed1ab_0
  - typing_extensions=4.9.0=py39h06a4308_1
  - urllib3=2.1.0=py39h06a4308_0
  - wheel=0.41.2=py39h06a4308_0
  - x264=1!161.3030=h7f98852_1
  - xorg-kbproto=1.0.7=h7f98852_1002
  - xorg-libice=1.0.10=h7f98852_0
  - xorg-libsm=1.2.3=hd9c2040_1000
  - xorg-libx11=1.7.2=h7f98852_0
  - xorg-libxau=1.0.9=h7f98852_0
  - xorg-libxdmcp=1.1.3=h7f98852_0
  - xorg-libxext=1.3.4=h7f98852_1
  - xorg-libxrender=0.9.10=h7f98852_1003
  - xorg-renderproto=0.11.1=h7f98852_1002
  - xorg-xextproto=7.3.0=h7f98852_1002
  - xorg-xproto=7.0.31=h7f98852_1007
  - xz=5.4.5=h5eee18b_0
  - yacs=0.1.8=pyhd8ed1ab_0
  - yaml=0.2.5=h7f98852_2
  - zlib=1.2.13=h5eee18b_0
  - zstd=1.5.5=hc292b87_0
  - pip:
      - asttokens==2.4.1
      - beautifulsoup4==4.12.3
      - blinker==1.7.0
      - chumpy==0.70
      - click==8.1.7
      - comm==0.2.2
      - contourpy==1.2.1
      - cycler==0.12.1
      - decorator==5.1.1
      - exceptiongroup==1.2.0
      - executing==2.0.1
      - filelock==3.13.1
      - flask==3.0.2
      - flask-cors==4.0.0
      - fonttools==4.51.0
      - gdown==5.1.0
      - importlib-metadata==7.0.1
      - importlib-resources==6.4.0
      - ipython==8.18.1
      - ipywidgets==8.1.2
      - itsdangerous==2.1.2
      - jedi==0.19.1
      - jinja2==3.1.3
      - joblib==1.4.0
      - jupyterlab-widgets==3.0.10
      - kiwisolver==1.4.5
      - kornia==0.7.1
      - markupsafe==2.1.5
      - matplotlib==3.8.4
      - matplotlib-inline==0.1.7
      - numpy==1.23.1
      - packaging==23.2
      - pandas==2.2.2
      - parso==0.8.4
      - pexpect==4.9.0
      - prompt-toolkit==3.0.43
      - ptyprocess==0.7.0
      - pure-eval==0.2.2
      - pygments==2.17.2
      - pyparsing==3.1.2
      - pysocks==1.7.1
      - python-dateutil==2.9.0.post0
      - pytz==2024.1
      - scikit-learn==1.4.2
      - scipy==1.12.0
      - seaborn==0.13.2
      - six==1.16.0
      - smplx==0.1.28
      - soupsieve==2.5
      - stack-data==0.6.3
      - threadpoolctl==3.4.0
      - torchgeometry==0.1.2
      - torchsummary==1.5.1
      - traitlets==5.14.2
      - tzdata==2024.1
      - wcwidth==0.2.13
      - werkzeug==3.0.1
      - widgetsnbextension==4.0.10
      - zipp==3.17.0
prefix: /home/hi/miniconda3/envs/4photo


'''