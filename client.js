import io from 'socket.io-client';

const socket = io('http://localhost:9000');
let btnTimer;

socket.on('web-pong', () => {
    document.getElementById('btnlabel').innerHTML = `${performance.now() - btnTimer} ms`
});
socket.on('circle-value', value => {
    document.getElementById('perimeter').innerHTML = `Circle perimeter: ${value}`;
});

function btnClick() {
    btnTimer = performance.now();
    socket.emit('web-ping');
}

function sliderChange() {
    const value = document.getElementById('slider').value;
    document.getElementById('sliderlabel').innerHTML = value;
    socket.emit('slider-change', value);
}

document.getElementById('btn').addEventListener('click', btnClick);
document.getElementById('slider').addEventListener('input', sliderChange);