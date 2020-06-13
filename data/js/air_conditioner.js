
function initWSClient(wsConnection) {
    ws = new WebSocket('ws://' + wsConnection.ip + ':' + wsConnection.port + '/temperature')
    ws.onopen = function (msg) {
        // Logic for opened connection
        console.log(msg);
    };
    ws.onmessage = function (msg) {
        temperature = JSON.parse(msg.data).temperature;
        $('#temperature').text("Temperature: " + temperature);
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
    let $minTempWidget = $("#min-temperature");
    $minTempWidget.attr("min", data.minTemperature);
    $minTempWidget.attr("max", data.maxTemperature);
    $minTempWidget.val(data.minTemperature);

    let $maxTempWidget = $("#max-temperature");
    $maxTempWidget.attr("min", data.minTemperature);
    $maxTempWidget.attr("max", data.maxTemperature);
    $maxTempWidget.val(data.maxTemperature);

    $minTempWidget.change(function(e) {
        if(e.target.value >= $maxTempWidget.val()) {
            $minTempWidget.val($maxTempWidget.val() - 1);
            e.preventDefault();
        }
    });

    $maxTempWidget.change(function(e) {
        if(e.target.value <= $minTempWidget.val()) {
            $maxTempWidget.val($minTempWidget.val() + 1);
            e.preventDefault();
        }
    });

    $('#save-temperature-range').click(function (e) {
        const payload = {
            minTemperature: $minTempWidget.val(),
            maxTemperature: $maxTempWidget.val()
        }
        $(event.target).attr("disabled", true);
        $.post("/updateTemperatureRange", JSON.stringify(payload), function (data) {
            $(event.target).attr("disabled", false);
        });
    });
}

$(document).ready(function () {

    $('#temperature').text("Temperature: reading...");
    $("#min-temperature").inputSpinner();
    $("#max-temperature").inputSpinner();

    $.getJSON('/getWebSocketServerAddress', function (data) {
        initWSClient(data);
    });


    $.getJSON('/getCurrentTemperatureRange', function (data) {
        initTemperatureRange(data);
    });

});