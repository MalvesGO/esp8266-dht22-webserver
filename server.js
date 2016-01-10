var express = require('express'),
app = express(),
http = require('http').Server(app),
io = require('socket.io'),
io = io.listen(http),
net = require('net'),
tcpServer = net.createServer(),
cors = require('cors'),
bodyParser = require('body-parser'),
path = require('path'),
url = require('url'),
fs = require('fs'),
sys = require(process.binding('natives').util ? 'util' : 'sys'),
listArduinos = [];

app.set('port', process.env.PORT || 8080);
app.use(cors());
app.use(bodyParser());
app.use(express.static(path.join(__dirname, 'app')));

app.get('/', function(req, res, next){
	res.sendfile('index.html');
});

app.get('/casa', function(req, res, next){
  res.sendfile('casa.html');
});

app.get('/empresa', function(req, res, next){
  res.sendfile('empresa.html');
});


// Arduino conecta no socket.
tcpServer.on('connection',function(socket){

  // Evento de recebimento de mensagem do arduino o nodejs.
  socket.on('data',function(data){

    // Convert the string into a JSON object:
    app.dados = JSON.parse(data)
    console.log( app.dados);

  })

  io.on("connection", function(socket){
    setInterval(function(){ 
      socket.emit("dadosClima", app.dados);
    }, 3000);
    
  });

});

http.listen(app.get('port'), function(){
	console.log('Servidor Nodejs online na porta: ' + app.get('port'));
});

tcpServer.listen(1337, function(){
	console.log('Socket disponível na porta: 8081');
});