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
    // const firmware_help     = document.getElementById("firmware_help" );
    const firmwareBt        = document.getElementById("firmwareBt"    );

    // firmware_help.innerText = "GitHub Firmware URL.\n https://raw.githubusercontent.com/<name>/<repo>/<branch>/<file path>/<file name>";

    get_github_json_url();

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

function get_github_json_url() {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/githubjson`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
    request.addEventListener("load", () => {
        let url = request.responseText;
        get_github_json_data(url) 
        console.log(`GitHub Json Url: ${url}`);
    });
}

function get_github_json_data(url) {
    var request = new XMLHttpRequest();
    request.open("GET", url, true);
    request.setRequestHeader("Accept", "application/vnd.github.v3+json");
    request.send();
    request.addEventListener("load", () => {
        let data = request.responseText;
        console.log(data);
        let last_ver = undefined;
        try {
            let data_json = JSON.parse(data)
            last_ver = data_json["tag_name"];
            document.getElementById('tag_title').innerText = data_json['name'];
            document.getElementById('release_body').innerText = data_json['body'];
        } catch(e) {
            last_ver = undefined;
            console.log("json error:", e);
        }
        get_esp_version(last_ver);
        get_bin_url(JSON.parse(data));
    });
}

function get_esp_version(last_ver) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/version`, true);
    request.send();
    request.addEventListener("load", () => {
        let now_ver = request.responseText;
        now_ver_span.innerText = now_ver;
        if(last_ver === undefined) {
            // last_ver_span.innerText = "NULL";
            document.getElementById('firmwareBt').disabled = true;
            document.getElementById('d_firmwareBt').disabled = true;
            now_ver_span.style.color = "gray";
            // last_ver_span.style.color = "gray";
        } else {
            // last_ver_span.innerText = last_ver;
            if(last_ver === now_ver) {
                document.getElementById('tag_title').style.color = "gray";
                document.getElementById('tag_title').innerText = "Now: " + document.getElementById('tag_title').innerText;
                now_ver_span.style.color = "gray";
                // last_ver_span.style.color = "gray";
                document.getElementById('d_firmwareBt').disabled = true;
            } else {
                document.getElementById('tag_title').style.color = "red";
                document.getElementById('tag_title').innerText = "New: " + document.getElementById('tag_title').innerText;
                now_ver_span.style.color = "orange";
                // last_ver_span.style.color = "red";
                update_link.style.color = "red";
            }
        }
    });
}

function get_bin_url(data) {
    try {
        let assets_list = data.assets;
        let spiffs_bin_url = undefined;
        let firmware_bin_url = undefined;

        for(let i = 0; i < assets_list.length; i++) {
            if(assets_list[i].name === "firmware.bin") {
                firmware_bin_url = assets_list[i].browser_download_url;
            }

            if(assets_list[i].name === "spiffs.bin") {
                spiffs_bin_url = assets_list[i].browser_download_url;
            }
        }    

        console.log("firmware bin url:", firmware_bin_url);
        console.log("spiffs bin url:", spiffs_bin_url);

        default_firmware_url = firmware_bin_url;
        document.getElementById('firmware_input').placeholder = default_firmware_url;
    }catch(e) {
        console.log("error:", e)
    }
}
