# socketio-cpp

An example project showcasing communication between a C++ client and a web client through node.js using socket.io.

## C++

Using the [socket.io-client-cpp](https://github.com/socketio/socket.io-client-cpp) library and relying *heavily* on the console example provided.
Additional Include Directories in the project expects boost to be under C:\boost\boost_1_73_0.. sorry.

## Javascript

Client side javascript is bundled by webpack and injected into html based on the `./index.html` template and both are outputted to `./dist` which is a static folder served by express on port 3000. Websockets communicate on port 9000.

### Scripts

```
npm install
```
to download modules.

```
npm run develop
```
to develop. Uses `nodemon` and `webpack --watch` to actively monitor for any changes in source files.

```
npm start
```
for "production". Builds and starts once.