const fan_on = document.getElementById('fan_on');
const fan_off = document.getElementById('fan_off');
const forward = document.getElementById('forward');
const backward = document.getElementById('backward');
const left = document.getElementById('left');
const right = document.getElementById('right');
const stop = document.getElementById('stop');

window.addEventListener('load', onLoad);

function onLoad() {
    initWebSocket();
}

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket("ws://" + window.location.hostname + "/ws");
    websocket.onopen = onOpen;
    websocket.onclose = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    console.log('Connection opened');
}

function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
}

function onMessage(event) {
    console.log("Msg[ESP32 DEV]:", event.data);
}

forward.addEventListener('click', () => {
    console.log('forward button click.');
    websocket.send("1");
});

backward.addEventListener('click', () => {
    console.log('backward button click.');
    websocket.send("2");
});

left.addEventListener('click', () => {
    console.log('left button click.');
    websocket.send("3");
});

right.addEventListener('click', () => {
    console.log('right button click.');
    websocket.send("4");
});

stop.addEventListener('click', () => {
    console.log('stop button click.');
    websocket.send("0");
});

fan_on.addEventListener('click', () => {
    console.log('fan_on button click.');
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/fan`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send("fan=255");
});

fan_off.addEventListener('click', () => {
    console.log('fan_off button click.');
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/fan`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send("fan=0");
});
