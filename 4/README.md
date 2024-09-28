







mac@macui-MacBookPro glory % nest new 4

⚡  We will scaffold your app in a few seconds..

? Which package manager would you ❤️  to use? npm
CREATE 4/.eslintrc.js (663 bytes)
CREATE 4/.prettierrc (51 bytes)
CREATE 4/README.md (4369 bytes)
CREATE 4/nest-cli.json (171 bytes)
CREATE 4/package.json (1940 bytes)
CREATE 4/tsconfig.build.json (97 bytes)
CREATE 4/tsconfig.json (546 bytes)
CREATE 4/src/app.controller.ts (274 bytes)
CREATE 4/src/app.module.ts (249 bytes)
CREATE 4/src/app.service.ts (142 bytes)
CREATE 4/src/main.ts (208 bytes)
CREATE 4/src/app.controller.spec.ts (617 bytes)
CREATE 4/test/jest-e2e.json (183 bytes)
CREATE 4/test/app.e2e-spec.ts (630 bytes)

✔ Installation in progress... ☕

🚀  Successfully created project 4
👉  Get started with the following commands:

$ cd 4
$ npm run start

                                         
                          Thanks for installing Nest 🙏
                 Please consider donating to our open collective
                        to help us maintain this package.
                                         
                                         
               🍷  Donate: https://opencollective.com/nest
                                         
mac@macui-MacBookPro glory % cd 4 
mac@macui-MacBookPro 4 % npm install axios sharp

added 11 packages, and audited 713 packages in 5s

114 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities
mac@macui-MacBookPro 4 % npm install @nestjs/axios

added 1 package, and audited 714 packages in 684ms

114 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities
mac@macui-MacBookPro 4 % nest generate service image 
CREATE src/image/image.service.spec.ts (453 bytes)
CREATE src/image/image.service.ts (89 bytes)
UPDATE src/app.module.ts (317 bytes)
mac@macui-MacBookPro 4 % nest generate controller image

CREATE src/image/image.controller.spec.ts (485 bytes)
CREATE src/image/image.controller.ts (99 bytes)
UPDATE src/app.module.ts (394 bytes)
mac@macui-MacBookPro 4 % npm run start                 


> 4@0.0.1 start
> nest start

src/image/image.service.ts:1:22 - error TS2724: '"@nestjs/common"' has no exported member named 'HttpService'. Did you mean 'HttpServer'?

1 import { Injectable, HttpService } from '@nestjs/common';
                       ~~~~~~~~~~~

Found 1 error(s).

mac@macui-MacBookPro 4 % npm install @nestjs/axios


up to date, audited 714 packages in 691ms

114 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities
mac@macui-MacBookPro 4 % npm run start            


> 4@0.0.1 start
> nest start

[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [NestFactory] Starting Nest application...
[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [InstanceLoader] HttpModule dependencies initialized +6ms
[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [InstanceLoader] AppModule dependencies initialized +0ms
[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [RoutesResolver] ImageController {/image}: +2ms
[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [RouterExplorer] Mapped {/image/fetch-and-process, GET} route +1ms
[Nest] 15119  - 09/28/2024, 11:24:38 PM     LOG [NestApplication] Nest application successfully started +1ms



mac@macui-MacBookPro 4 % npm install axios sharp

added 11 packages, and audited 713 packages in 5s

114 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities

mac@macui-MacBookPro 4 % nest generate service image 
CREATE src/image/image.service.spec.ts (453 bytes)
CREATE src/image/image.service.ts (89 bytes)
UPDATE src/app.module.ts (317 bytes)
mac@macui-MacBookPro 4 % nest generate controller image

CREATE src/image/image.controller.spec.ts (485 bytes)
CREATE src/image/image.controller.ts (99 bytes)
UPDATE src/app.module.ts (394 bytes)


mac@macui-MacBookPro 4 % npm install @nestjs/axios


up to date, audited 714 packages in 691ms

114 packages are looking for funding
  run `npm fund` for details

found 0 vulnerabilities










<p align="center">
  <a href="http://nestjs.com/" target="blank"><img src="https://nestjs.com/img/logo-small.svg" width="120" alt="Nest Logo" /></a>
</p>

[circleci-image]: https://img.shields.io/circleci/build/github/nestjs/nest/master?token=abc123def456
[circleci-url]: https://circleci.com/gh/nestjs/nest

  <p align="center">A progressive <a href="http://nodejs.org" target="_blank">Node.js</a> framework for building efficient and scalable server-side applications.</p>
    <p align="center">
<a href="https://www.npmjs.com/~nestjscore" target="_blank"><img src="https://img.shields.io/npm/v/@nestjs/core.svg" alt="NPM Version" /></a>
<a href="https://www.npmjs.com/~nestjscore" target="_blank"><img src="https://img.shields.io/npm/l/@nestjs/core.svg" alt="Package License" /></a>
<a href="https://www.npmjs.com/~nestjscore" target="_blank"><img src="https://img.shields.io/npm/dm/@nestjs/common.svg" alt="NPM Downloads" /></a>
<a href="https://circleci.com/gh/nestjs/nest" target="_blank"><img src="https://img.shields.io/circleci/build/github/nestjs/nest/master" alt="CircleCI" /></a>
<a href="https://coveralls.io/github/nestjs/nest?branch=master" target="_blank"><img src="https://coveralls.io/repos/github/nestjs/nest/badge.svg?branch=master#9" alt="Coverage" /></a>
<a href="https://discord.gg/G7Qnnhy" target="_blank"><img src="https://img.shields.io/badge/discord-online-brightgreen.svg" alt="Discord"/></a>
<a href="https://opencollective.com/nest#backer" target="_blank"><img src="https://opencollective.com/nest/backers/badge.svg" alt="Backers on Open Collective" /></a>
<a href="https://opencollective.com/nest#sponsor" target="_blank"><img src="https://opencollective.com/nest/sponsors/badge.svg" alt="Sponsors on Open Collective" /></a>
  <a href="https://paypal.me/kamilmysliwiec" target="_blank"><img src="https://img.shields.io/badge/Donate-PayPal-ff3f59.svg" alt="Donate us"/></a>
    <a href="https://opencollective.com/nest#sponsor"  target="_blank"><img src="https://img.shields.io/badge/Support%20us-Open%20Collective-41B883.svg" alt="Support us"></a>
  <a href="https://twitter.com/nestframework" target="_blank"><img src="https://img.shields.io/twitter/follow/nestframework.svg?style=social&label=Follow" alt="Follow us on Twitter"></a>
</p>
  <!--[![Backers on Open Collective](https://opencollective.com/nest/backers/badge.svg)](https://opencollective.com/nest#backer)
  [![Sponsors on Open Collective](https://opencollective.com/nest/sponsors/badge.svg)](https://opencollective.com/nest#sponsor)-->

## Description

[Nest](https://github.com/nestjs/nest) framework TypeScript starter repository.

## Project setup

```bash
$ npm install
```

## Compile and run the project

```bash
# development
$ npm run start

# watch mode
$ npm run start:dev

# production mode
$ npm run start:prod
```

## Run tests

```bash
# unit tests
$ npm run test

# e2e tests
$ npm run test:e2e

# test coverage
$ npm run test:cov
```

## Resources

Check out a few resources that may come in handy when working with NestJS:

- Visit the [NestJS Documentation](https://docs.nestjs.com) to learn more about the framework.
- For questions and support, please visit our [Discord channel](https://discord.gg/G7Qnnhy).
- To dive deeper and get more hands-on experience, check out our official video [courses](https://courses.nestjs.com/).
- Visualize your application graph and interact with the NestJS application in real-time using [NestJS Devtools](https://devtools.nestjs.com).
- Need help with your project (part-time to full-time)? Check out our official [enterprise support](https://enterprise.nestjs.com).
- To stay in the loop and get updates, follow us on [X](https://x.com/nestframework) and [LinkedIn](https://linkedin.com/company/nestjs).
- Looking for a job, or have a job to offer? Check out our official [Jobs board](https://jobs.nestjs.com).

## Support

Nest is an MIT-licensed open source project. It can grow thanks to the sponsors and support by the amazing backers. If you'd like to join them, please [read more here](https://docs.nestjs.com/support).

## Stay in touch

- Author - [Kamil Myśliwiec](https://twitter.com/kammysliwiec)
- Website - [https://nestjs.com](https://nestjs.com/)
- Twitter - [@nestframework](https://twitter.com/nestframework)

## License

Nest is [MIT licensed](https://github.com/nestjs/nest/blob/master/LICENSE).
