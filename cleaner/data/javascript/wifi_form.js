function init_wifi_form() {
    const wifi_ssid_input   = document.getElementById("wifi_ssid_input"  );
    const wifi_passwd_input = document.getElementById("wifi_passwd_input");
    const wifiBt            = document.getElementById("wifiBt"           );

    get_esp_ssid(wifi_ssid_input);

    wifiBt.addEventListener('click', () => {
        console.log(`wifi_ssid_input.value:   ${wifi_ssid_input.value}`  );
        console.log(`wifi_passwd_input.value: ${wifi_passwd_input.value}`);
        esp32_wifi_update(wifi_ssid_input.value, wifi_passwd_input.value  );
    });
}

function init_ap_form() {
    const ap_ssid_input   = document.getElementById("ap_ssid_input"  );
    const ap_passwd_input = document.getElementById("ap_passwd_input");
    const apBt            = document.getElementById("apBt"           );

    apBt.addEventListener('click', () => {
        console.log(`ap_ssid_input.value:   ${ap_ssid_input.value}`  );
        console.log(`ap_passwd_input.value: ${ap_passwd_input.value}`);
        esp32_ap_update(ap_ssid_input.value, ap_passwd_input.value  );
    });
}

function esp32_ap_update(ssid, passwd) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/data`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    if(ssid == "" && passwd == "");

    if(ssid != "" && passwd == "")
        request.send(`2=${ssid}`);
    if(ssid == "" && passwd != "")
        request.send(`3=${passwd}`);
    if(ssid != "" && passwd != "")
        request.send(`2=${ssid}&3=${passwd}`);
}

function esp32_wifi_update(ssid, passwd) {
    setAllBut(true);

    try {
        var request = new XMLHttpRequest();
        request.open("POST", `${window.location.origin}/set/data`, true);
        request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
        if(ssid == "" && passwd == "");

        if(ssid != "" && passwd == "")
            request.send(`0=${ssid}`);
        if(ssid == "" && passwd != "")
            request.send(`1=${passwd}`);
        if(ssid != "" && passwd != "")
            request.send(`0=${ssid}&1=${passwd}`);
        
        request.addEventListener("load", () => {
            window.location.reload();
        });
    } catch(e) {
        setAllBut(false);
    }
}

function get_esp_ssid(wifi_ssid_input) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/get/wifi/ssid`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send();
    request.addEventListener("load", () => {
        wifi_ssid_input.placeholder = request.responseText;
        console.log(`WiFi SSID: ${request.responseText}`);
    });
}
