
/*
	this is a simple server
*/

var express = require('express');

var app = express();

var port = 3700;
	
//var http = require('http').Server(app);

//var io = require('socket.io')(http);

//for using jade with express js
app.set('views', __dirname + '/tpl');
app.set('view engine', "jade");
app.engine('jade', require('jade').__express);
app.get("/", function(req, res){
    res.render("page");
});
	
app.get('/', function(req, res){
	
	res.send('it works!');
	//res.sendFile(__dirname + '/index.html');
		
});
	
//http.listen(3000, function() {
		
//	console.log('listening on *:3000');
		

		
app.use(express.static(__dirname + '/public'));

var io = require('socket.io').listen(app.listen(port));
console.log('listening on port: ' + port);

//socket is actually the socket of the client
io.sockets.on('connection', function (socket) {
    socket.emit('message', { message: 'welcome to the chat' });
    socket.on('send', function (data) {
        io.sockets.emit('message', data);
    });
});