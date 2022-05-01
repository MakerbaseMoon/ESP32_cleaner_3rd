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
    let A01_value = document.getElementById('A01_value').value;
    let A02_value = document.getElementById('A02_value').value;
    let B01_value = document.getElementById('B01_value').value;
    let B02_value = document.getElementById('B02_value').value;

    if(A01_value == "") {
        A01_value = document.getElementById('A01_value').placeholder;
    }

    if(A02_value == "") {
        A02_value = document.getElementById('A02_value').placeholder;
    }

    if(B01_value == "") {
        B01_value = document.getElementById('B01_value').placeholder;
    }

    if(B02_value == "") {
        B02_value = document.getElementById('B02_value').placeholder;
    }

    A01_value = parseInt(A01_value);
    A02_value = parseInt(A02_value);
    B01_value = parseInt(B01_value);
    B02_value = parseInt(B02_value);

    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    let byteArray = new Uint8Array([54, 61, value + 48, A01_value, A02_value, B01_value, B02_value]);
    request.send(byteArray);
}

function get_motor_data() {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/motor`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
    request.addEventListener("load", () => {
        let data = request.responseText;
        let data_list = data.split(",", 5);
        console.log("data:", data);

        try {
            let num = parseInt(data_list[0]);
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

            document.getElementById('A01_value').placeholder = data_list[1];
            document.getElementById('A02_value').placeholder = data_list[2];
            document.getElementById('B01_value').placeholder = data_list[3];
            document.getElementById('B02_value').placeholder = data_list[4];
        } catch(e) {
            console.log("Error:", e);
        }
    });
}
