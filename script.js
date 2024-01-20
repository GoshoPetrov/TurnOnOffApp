

function sendRequest(ipId, action) {
    const ip = getIp(ipId);
    showMessage(ipId, `Turning ${ip} ${action}...`);

    fetch(`http://${ip}/${action}`)
        .then(response => {
            if (!response.ok) {
                showMessage(ipId, `HTTP error! Status: ${response.status}`);
            }
            return response.text();
        })
        .then(data => {
            showMessage(ipId, `Data received: ${data}`);
        })
        .catch(error => {
            // Handle errors that occurred during the fetch
            showMessage(ipId, `Fetch error: ${error}`);
        });

}

function onTurnOn(id) {
    sendRequest(id, "on");
}

function onTurnOff(id) {
    sendRequest(id, "off");
}

function showMessage(id, message) {
    const msg = document.getElementById(`${id}msg`);
    msg.innerHTML = message;
}

function getIp(id) {
    const ipElement = document.getElementById(id);
    return ipElement.value;
}

function onCheck(id, ) {
    showMessage(id, "The IP is checking...");
}

var started = {};
function readTemp(ipId){
    if (started[ipId]) {
        console.log(`${ipId} already started...`);
        return;
    }

    console.log(`${ipId} starting ...`);
    started[ipId] = true;
    var again = () => {
        sendRequest(ipId, "temp");
        setTimeout(again, 5000);
    };

    again();
}