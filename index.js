import express from 'express';
import http from 'http';
import io from 'socket.io';

const httpPort = 3000;
const wsPort = 9000;
const app = express();
const httpServer = http.createServer(app);
const wsServer = io.listen(wsPort);

app.use(express.static('dist'));

httpServer.listen(httpPort, () => {
    console.log(`Listening to HTTP requests on port ${httpPort}`);
});

wsServer.on('connection', socket => {
    console.log('User connected');
});

console.log(`Listening to WebSocket requests on port ${wsPort}`);