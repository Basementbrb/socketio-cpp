import io from 'socket.io-client';

const socket = io('http://localhost:9000');
let btnTimer;

socket.on('web-pong', () => {
    document.getElementById('btnlabel').innerHTML = `${performance.now() - btnTimer} ms`
});

function btnClick() {
    btnTimer = performance.now();
    socket.emit('web-ping');
}

document.getElementById('btn').addEventListener('click', btnClick);