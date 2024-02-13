document.getElementById('connexion').hidden = false;
document.getElementById('table').hidden = true;

/* WebSocket connexion */
document.getElementById('connect').addEventListener('click', function() {
    var serverName  = document.getElementById('serverName').value;
    var hostName    = document.getElementById('hostName').value;
    var userName    = document.getElementById('userName').value;
    var password    = document.getElementById('password').value;
    var dbName      = document.getElementById('dbName').value;

    var socket = new WebSocket("ws://"+ serverName +":3006");

    var serial  = document.getElementById('serial');
    var tcp     = document.getElementById('tcp');

    /* WebSocket open */
    socket.onopen = function() {
        document.getElementById('connexion').hidden = true;
        document.getElementById('table').hidden = false;

        var data = "connection;"+serverName+";"+hostName+";"+userName+";"+password+";"+dbName;
        socket.send(data);

        console.log("Client WebSocket: Nouvelle connexion");
    };

    /* Send serial value on the server */
    serial.onclick = function() {
        socket.send("serial");
    };

    /* Send serial value on the server */
    tcp.onclick = function() {
        socket.send("tcp");
    };

    /* WebSocket close */
    socket.onclose = function() {
        document.getElementById('connexion').hidden = false;
        document.getElementById('table').hidden = true;

        console.log("Client WebSocket: Deconnexion");
    };

    /* WebSocket error */
    socket.onerror = function(error) {
        console.error(error);
    };
            
    /* Receive message of the server */
    socket.onmessage = function(event) {
        var message     = event.data;
        var regex       = /[^;]+/g;
        const messageContent = [message.match(regex)];

        point(messageContent);

        var tblBody     = document.getElementById('tbody');
        var row         = document.createElement("tr");
        for(var i = 0; i < messageContent[0].length; i++) {
            var cell        = document.createElement("td");
            var cellText    = document.createTextNode(messageContent[0][i])
            cell.appendChild(cellText);
            row.appendChild(cell);
        }
        tblBody.appendChild(row);
        tblBody.scrollTop = tblBody.scrollHeight;
    };

    /* WebSocket disconnexion */
    document.getElementById('disconnect').addEventListener('click', function() {
        socket.close();
    });
});