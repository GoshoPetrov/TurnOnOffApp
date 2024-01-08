

function sendRequest(action) {
    const ip = getIp();
    showMessage(`Turning ${ip} ${action}...`);

    fetch(`http://${ip}/${action}`)
        .then(response => {
            if (!response.ok) {
                showMessage(`HTTP error! Status: ${response.status}`);
            }
            return response.text();
        })
        .then(data => {
            showMessage(`Data received: ${data}`);
        })
        .catch(error => {
            // Handle errors that occurred during the fetch
            showMessage(`Fetch error: ${error}`);
        });

}

function onTurnOn() {
    sendRequest("on");
}

function onTurnOff() {
    sendRequest("off");
}

function showMessage(message) {
    const msg = document.getElementById("msg");
    msg.innerHTML = message;
}

function getIp() {
    const ipElement = document.getElementById("ip");
    return ipElement.value;
}

function onCheck() {
    showMessage("The IP is checking...");
}