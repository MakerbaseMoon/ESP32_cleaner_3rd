let default_firmware_url;

function init_spiffs_form() {
    const spiffs_input    = document.getElementById("spiffs_input");
    const spiffs_help     = document.getElementById("spiffs_help" );
    const spiffsBt        = document.getElementById("spiffsBt"    );

    spiffs_help.innerText = "GitHub Firmware URL.\n https://raw.githubusercontent.com/<name>/<repo>/<branch>/<file path>/<file name>";

    spiffsBt.addEventListener('click', () => {
        console.log(`spiffs_input.value: ${spiffs_input.value}`);
        esp32_ota_update(3, spiffs_input.value);
    });
}

function init_firmware_form() {
    const firmware_input    = document.getElementById("firmware_input");
    const firmware_help     = document.getElementById("firmware_help" );
    const firmwareBt        = document.getElementById("firmwareBt"    );

    esp32_ota_update_url(firmware_input);
    firmware_help.innerText = "GitHub Firmware URL.\n https://raw.githubusercontent.com/<name>/<repo>/<branch>/<file path>/<file name>";

    firmwareBt.addEventListener('click', () => {
        if(firmware_input.value == "")
        firmware_input.value = default_firmware_url;
        console.log(`firmware_input.value: ${firmware_input.value}`);
        esp32_ota_update(2, firmware_input.value);
        firmwareBt.disabled   = true;
        d_firmwareBt.disabled = true;
    });
    
    d_firmwareBt.addEventListener('click', () => {
        console.log(`firmware_input.value: ${default_firmware_url}`);
        esp32_ota_update(2, default_firmware_url);
        firmwareBt.disabled   = true;
        d_firmwareBt.disabled = true;
    });
}

function init_token_form() {
    const token_input    = document.getElementById("token_input");
    const token_help     = document.getElementById("token_help" );
    const tokenBt        = document.getElementById("tokenBt"    );

    token_help.innerText = "ght_XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

    tokenBt.addEventListener('click', () => {
        console.log(`tokenBt click.`);
        esp32_token_update(token_input.value);
    });
}

function esp32_ota_update_url(firmware_help) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/firmware`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`type=firmware`);
    request.addEventListener("load", () => {
        firmware_input.placeholder = request.responseText;
        default_firmware_url = request.responseText;
        console.log(`firmware url: ${request.responseText}`);
    });
}

function esp32_ota_update(type, url) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/ota/update`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`${type}=${url}`);
}

function esp32_token_update(token) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`5=${token}`);
}
