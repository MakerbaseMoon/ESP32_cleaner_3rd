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

    get_motor_data();
    
    document.getElementById('motorBt').addEventListener('click', () => {
        let a_value = document.getElementById('motorACheck').checked;
        let b_value = document.getElementById('motorBCheck').checked;

        if(!a_value && !b_value) {
            motor_update(0);
        } else if(a_value && !b_value) {
            motor_update(1);            
        } else if(!a_value && b_value) {
            motor_update(2);            
        } else if(a_value && b_value) {
            motor_update(3);            
        }
    });
}

function motor_update(value) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`6=${value}`);
}

function get_motor_data() {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/motor`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
    request.addEventListener("load", () => {
        let data = request.responseText;
        console.log(data);
        try {
            let num = parseInt(data);
            if(num == 0) {
                document.getElementById('motorACheck').checked = false;
                document.getElementById('motorBCheck').checked = false;
            } else if(num == 1) {
                document.getElementById('motorACheck').checked = true;
                document.getElementById('motorBCheck').checked = false;
            }  else if(num == 2) {
                document.getElementById('motorACheck').checked = false;
                document.getElementById('motorBCheck').checked = true;
            }  else if(num == 3) {
                document.getElementById('motorACheck').checked = true;
                document.getElementById('motorBCheck').checked = true;
            }
        } catch(e) {
            console.log("Error:", e);
        }
    });
}

