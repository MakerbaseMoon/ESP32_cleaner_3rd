const update_button = document.getElementById('update_button');
const update_input = document.getElementById('update_input');

update_button.addEventListener('click', () => {
    console.log('update_button button click.');
    var request = new XMLHttpRequest();
    request.open("POST", `${window.location.origin}/ota`, true);
    request.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    request.send(`url=${update_input.value}`);
});
