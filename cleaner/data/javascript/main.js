window.addEventListener('load', onLoad);
window.addEventListener("resize", set_div);

const col1  = document.getElementById("col1");
const col2  = document.getElementById("col2");
const col3  = document.getElementById("col3");

const now_ver_span   = document.getElementById("now_ver_span");
const last_ver_span  = document.getElementById("last_ver_span");

const update_link    = document.getElementById("update_link");

const setting        = document.getElementById("setting")

let mode = 0;

function onLoad() {
    set_div();
    init_firmware_form();
    // init_spiffs_form();
    
    init_wifi_form();

    init_fan_button();
    init_motor_button();

    document.getElementById("modeBt").addEventListener('click', change_mode);
    document.getElementById("cleanBt").addEventListener('click', clean_eeprom_data);
    // init_ap_form();
    // init_token_form();
    // document.getElementById("mdnsBt").addEventListener('click', esp32_mdns_update);
    get_github_json_url();
    initWebSocket();
}

function clean_eeprom_data() {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/clean/eeprom`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
}

function change_mode() {
    const modeBt    = document.getElementById("modeBt");
    const mode_span = document.getElementById("mode_span");
    const card_div  = document.getElementById("card_div");

    if(mode == 0) {
        console.log("[Mode] Auto -> Control");
        mode_span.innerText = "Control";
        card_div.innerHTML = "";
        card_div.appendChild(getControllerIcon(300, 300));
        modeBt.innerHTML = "";
        modeBt.appendChild(getAutoIcon(60, 60));
        esp32_mode_update(1);
        for(let i = 1; i < 5; i++) {
            document.getElementById(`motorBt${i}`).disabled = false;
        }
        mode = 1;
    } else if(mode == 1) {;
        console.log("[Mode] Control -> Auto");
        card_div.innerHTML = "";
        let auto_svg =  getAutoIcon(300, 300);
        auto_svg.classList.add("retate_svg");
        card_div.appendChild(auto_svg);

        modeBt.innerHTML = "";
        modeBt.appendChild(getControllerIcon(60, 60));
        mode_span.innerText = "Auto";
        esp32_mode_update(0);
        for(let i = 1; i < 5; i++) {
            document.getElementById(`motorBt${i}`).disabled = true;
        }
        mode = 0;
    }
}

function esp32_mdns_update() {
    let mdns = document.getElementById("mdns_input").value;
    if(mdns == "")
        return;
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`4=${mdns}`);
}


function esp32_mode_update(value) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/mode`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`mode=${value}`);
}

function getAutoIcon(width, height) {
    return getIcon("bi bi-arrow-repeat",
                   "M11.534 7h3.932a.25.25 0 0 1 .192.41l-1.966 2.36a.25.25 0 0 1-.384 0l-1.966-2.36a.25.25 0 0 1 .192-.41zm-11 2h3.932a.25.25 0 0 0 .192-.41L2.692 6.23a.25.25 0 0 0-.384 0L.342 8.59A.25.25 0 0 0 .534 9z",
                   "M8 3c-1.552 0-2.94.707-3.857 1.818a.5.5 0 1 1-.771-.636A6.002 6.002 0 0 1 13.917 7H12.9A5.002 5.002 0 0 0 8 3zM3.1 9a5.002 5.002 0 0 0 8.757 2.182.5.5 0 1 1 .771.636A6.002 6.002 0 0 1 2.083 9H3.1z",
                   width,
                   height
    )
}

function getControllerIcon(width, height) {
    return getIcon("bi bi-controller",
                   "M11.5 6.027a.5.5 0 1 1-1 0 .5.5 0 0 1 1 0zm-1.5 1.5a.5.5 0 1 0 0-1 .5.5 0 0 0 0 1zm2.5-.5a.5.5 0 1 1-1 0 .5.5 0 0 1 1 0zm-1.5 1.5a.5.5 0 1 0 0-1 .5.5 0 0 0 0 1zm-6.5-3h1v1h1v1h-1v1h-1v-1h-1v-1h1v-1z",
                   "M3.051 3.26a.5.5 0 0 1 .354-.613l1.932-.518a.5.5 0 0 1 .62.39c.655-.079 1.35-.117 2.043-.117.72 0 1.443.041 2.12.126a.5.5 0 0 1 .622-.399l1.932.518a.5.5 0 0 1 .306.729c.14.09.266.19.373.297.408.408.78 1.05 1.095 1.772.32.733.599 1.591.805 2.466.206.875.34 1.78.364 2.606.024.816-.059 1.602-.328 2.21a1.42 1.42 0 0 1-1.445.83c-.636-.067-1.115-.394-1.513-.773-.245-.232-.496-.526-.739-.808-.126-.148-.25-.292-.368-.423-.728-.804-1.597-1.527-3.224-1.527-1.627 0-2.496.723-3.224 1.527-.119.131-.242.275-.368.423-.243.282-.494.575-.739.808-.398.38-.877.706-1.513.773a1.42 1.42 0 0 1-1.445-.83c-.27-.608-.352-1.395-.329-2.21.024-.826.16-1.73.365-2.606.206-.875.486-1.733.805-2.466.315-.722.687-1.364 1.094-1.772a2.34 2.34 0 0 1 .433-.335.504.504 0 0 1-.028-.079zm2.036.412c-.877.185-1.469.443-1.733.708-.276.276-.587.783-.885 1.465a13.748 13.748 0 0 0-.748 2.295 12.351 12.351 0 0 0-.339 2.406c-.022.755.062 1.368.243 1.776a.42.42 0 0 0 .426.24c.327-.034.61-.199.929-.502.212-.202.4-.423.615-.674.133-.156.276-.323.44-.504C4.861 9.969 5.978 9.027 8 9.027s3.139.942 3.965 1.855c.164.181.307.348.44.504.214.251.403.472.615.674.318.303.601.468.929.503a.42.42 0 0 0 .426-.241c.18-.408.265-1.02.243-1.776a12.354 12.354 0 0 0-.339-2.406 13.753 13.753 0 0 0-.748-2.295c-.298-.682-.61-1.19-.885-1.465-.264-.265-.856-.523-1.733-.708-.85-.179-1.877-.27-2.913-.27-1.036 0-2.063.091-2.913.27z",
                   width,
                   height
    )
}

function getIcon(_class, _path1, _path2, width, height) {
    var xmlns = "http://www.w3.org/2000/svg";
    var svg   = document.createElementNS(xmlns, "svg");

    svg.setAttributeNS(null, "width",   width);
    svg.setAttributeNS(null, "height",  height);
    svg.setAttributeNS(null, "fill",    "currentColor");
    svg.setAttributeNS(null, "class",   _class);
    svg.setAttributeNS(null, "viewBox", "0 0 16 16");
    if(_path1 != "") {
        var path = document.createElementNS(xmlns, "path");
        path.setAttributeNS(null, "d", _path1);
        svg.appendChild(path);
    }

    var path2 = document.createElementNS(xmlns, "path");
    path2.setAttributeNS(null, "d", _path2);
    svg.appendChild(path2);

    return svg;
}

function set_div() {
    if(outerWidth < 400) {
        col1.classList = [];
        col3.classList = [];
        col1.classList.add("col-1");
        col3.classList.add("col-1");
    } else if(outerWidth < 850) {
        col1.classList = [];
        col3.classList = [];
        col1.classList.add("col-2");
        col3.classList.add("col-2");
    } else {
        col1.classList = [];
        col3.classList = [];
        col1.classList.add("col-3");
        col3.classList.add("col-3");
    }
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
            last_ver = JSON.parse(data)["tag_name"];
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
            last_ver_span.innerText = "NULL";
            document.getElementById('firmwareBt').disabled = true;
            document.getElementById('d_firmwareBt').disabled = true;
            now_ver_span.style.color = "gray";
            last_ver_span.style.color = "gray";
        } else {
            last_ver_span.innerText = last_ver;
            if(last_ver === now_ver) {
                now_ver_span.style.color = "gray";
                last_ver_span.style.color = "gray";
                document.getElementById('d_firmwareBt').disabled = true;
            } else {
                now_ver_span.style.color = "orange";
                last_ver_span.style.color = "red";
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
    }catch(e) {
        console.log("error:", e)
    }
}
