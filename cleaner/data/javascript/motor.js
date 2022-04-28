let websocket;

function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket           = new WebSocket("ws://" + window.location.hostname + "/ws");
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
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

function send_motor_message(msg) {
    websocket.send(msg);
}

function init_motor_button() {
    for(let i = 1; i < 5; i++) {
        document.getElementById(`motorBt${i}`).addEventListener('mousedown', () => {
            console.log(`motorBt${i} click.`);
            websocket.send(i);
        });

        document.getElementById(`motorBt${i}`).addEventListener('mouseup', () => {
            console.log(`motorBt${i} click.`);
            websocket.send(0);
        });

        document.getElementById(`motorBt${i}`).addEventListener('touchstart', () => {
            console.log(`motorBt${i} click.`);
            websocket.send(i);
        });

        document.getElementById(`motorBt${i}`).addEventListener('touchend', () => {
            console.log(`motorBt${i} click.`);
            websocket.send(0);
        });
    }
}

function motor_update(value) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`6=${value}`);
}
