import express from 'express';
import http from 'http';

const app = express();
const server = http.createServer(app);
const port = process.env.port || 9000;

app.get('/', (request, response) => {
    response.send('<h1>Hello world</h1>');
});

server.listen(port, () => {
    console.log(`Listening on port ${port}`);
});