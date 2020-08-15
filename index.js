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
    socket.on('disconnect', () => {
        console.log('User disconnected');
    });
    socket.on('web-ping', () => {
        console.log('ping from web');
        socket.broadcast.emit('cpp-ping');
    });
    socket.on('cpp-pong', () => {
        console.log('pong from cpp');
        socket.broadcast.emit('web-pong');
    });
});

console.log(`Listening to WebSocket requests on port ${wsPort}`);