# Rerunner
## Kino Rose

An implementation of an infinite runner game using ReasonML and Reprocessing.

## Technologies
* ReasonML
* Reprocessing

## How To Run

### Clone
```
git clone hhttps://github.com/KinoAR/rerunner.git
```

### Install

```
npm install
```

### Build
```
npm run build
```

### Start
```
npm start
```

To build to JS run `npm run build:web` and then run a static server, like `python -m SimpleHTTPServer` and go to `localhost:8000`. If you're using safari you can simply open the `index.html` and tick `Develop > Disable Cross-Origin Restrictions`.

To build to native run `npm run build:native` and run `npm run start:native`

The build system used is [bsb-native](https://github.com/bsansouci/bucklescript).

## How To Play