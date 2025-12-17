//출처 : https://llama-node.vercel.app/docs/start
//출처 : https://www.youtube.com/watch?v=_tUDZdlehAk

import { LLM } from "llama-node"
import { LLamaCpp } from "llama-node/dist/llm/llama-cpp.js"
import express from 'express'
import path from 'path'
const app = express ()
const llama = new LLM(LLamaCpp)

app.listen (3000, () => {
    console. log("server started http://127.0.0.1:3000")
})
app.get('/', async (req, res) => {
    res. sendFile(path.join(path.resolve(), '/index.html'));
})


//http://127.0.0.1:3000/ask
app.get('/ask', async (rea, res) => {
    res.writeHead(200, {'content-type': 'text/html'} )
    await llama. load({
        modelPath: "model/airoboros-13b-gpt4.ggmlv3.q4_0.bin",
        enableLogging: false, nCtx: 1024,
        seed: 0, f16Kv: false, logitsAll: false, vocabOnly: false,
        useMlock: false, embedding: false, useMmap: true, nGpuLayers: 0
    })
    await llama. createCompletion({
        prompt: "what is your favorite movie",
        nThreads: 4, nTokPredict: 2048,
        topk: 40, topP: 0.1, temp: 0.3, repeatPenalty: 1, //temp: 0.3 or 0.2
    }, (response) => {
    res.write(response.token)
    })
})