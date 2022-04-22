function init_fan_button() {
    for(let i = 0; i < 4; i ++) {
        document.getElementById(`fanBt${i}`).addEventListener('click', () => {
            console.log(`fanBt${i} click.`);
            esp32_fan_pwm_update(i);
        });
    }
}

function esp32_fan_pwm_update(value) {
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/set/fan`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`pwm=${value}`);
}