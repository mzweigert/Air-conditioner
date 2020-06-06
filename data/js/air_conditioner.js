
function initWSClient(wsConnection) {
    ws = new WebSocket('ws://' + wsConnection.ip + ':' + wsConnection.port + '/temperature')
    ws.onopen = function (msg) {
        // Logic for opened connection
        console.log(msg);
    };
    ws.onmessage = function (msg) {
        temperature = JSON.parse(msg.data).temperature;
        $('#temperature').text("Temperature: " + temperatureInfo.temperature);
    };

    ws.onclose = function (msg) {
        // Logic for closed connection
        console.log('Connection was closed.');
    }

    ws.error = function (err) {
        console.log(err); // Write errors to console
    }
}

function initTemperatureRange(data) {
    $( "#min-temperature" ).spinner('value', data.minimumTemperature);
    $( "#max-temperature" ).spinner('value', data.maximumTemperature);
    
}

$(document).ready(function () {

    $.getJSON('/getWebSocketServerAddress', function (data) {
        initWSClient(data);
    });


    $.getJSON('/getCurrentTemperatureRange', function (data) {
        initTemperatureRange(data);
    });

});