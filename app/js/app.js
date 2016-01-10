var socket = new io.connect({ port: 8080, rememberTransport: false});

$(document).ready(function () {

    var socket = io();

    socket.on('dadosClima', function (data) {
        var arduino = (data);
        $('#hora').text(getDateTime());
        $('#temperatura').text(arduino.temperatura);
        $('#umidade').text(arduino.umidade);
    });

    function getDateTime() {

        var date = new Date();

        var hour = date.getHours();
        hour = (hour < 10 ? "0" : "") + hour;

        var min  = date.getMinutes();
        min = (min < 10 ? "0" : "") + min;

        return hour + ":" + min;
    }
    
});


