function onTurnOn() {
    showMessage(`Turning ${getIp()} on...`);
}

function onTurnOff(){
    showMessage(`Turning ${getIp()} off...`);

}

function showMessage(message) {
    const msg = document.getElementById("msg");
    msg.innerHTML = message;
}

function getIp() {
    const ipElement = document.getElementById("ip");
    return ipElement.value;
}

function onCheck(){
    showMessage("The IP is checking...");
}