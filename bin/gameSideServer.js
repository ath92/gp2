//var TRACKERPC = '130.89.243.9';
//var GAMEHOST = '130.89.13.44'; //LAPTOP
//var GAMEHOST = '130.89.27.206'; //UNITY PC
//var GAMEHOST = '130.89.243.222'; //Unity PC
//Z9789\DesignLabHMI
//Parle$vink0

//9009 tracker <> forwarder
//9001 forwarde <> gamesidenode
//9000 gamesidenode <> game

//TCP/IP protocol FOR THE GAME to connect to
var net   = require('net');
var clients = [];


//create a text file
//no var needed?
// fs = require('fs');
// fs.writeFile('gameside.txt', 'Hello World!', function (err) {
  // if (err) return console.log(err);
  // console.log('created gameside.txt');
// });

//create a TCP server
net.createServer(function(socket) {
	console.log("Client tries to connect");
	try {
		socket.name = socket.remoteAddress + ":" + socket.remotePort; 
		//according to documentation this is already the default setting!
		socket.setNoDelay= true;
		clients.push(socket);
		socket.on('end', function() {
			removeClient(socket);
		});
		//also remove client on error
		socket.on('error', function() {
			removeClient(socket);
		});
		console.log("Client is connected");
	} catch (err) {
		console.log("client had error during connection: " + err);
		//removeClient(client);
	}
}).listen(9009, "0.0.0.0");
//TODO try with 127.0.0.1



////////// Listens to the Kinect tracker forwarder//////
var PORT = 9003;

//var HOST = '127.0.0.1';
var TRACKERHOST = '130.89.243.9';

var dgram = require('dgram');
var server = dgram.createSocket('udp4');
//for debugging / checking update speed
var currentTime =(new Date()).getTime();
var lastTime = currentTime;
var currentTimeClient = (new Date()).getTime();
var lastTimeClient = currentTimeClient;


server.on('listening', function () {
    var address = server.address();
    console.log('UDP Server listening on ' + address.address + ":" + address.port);
});

server.on('message', function (message, remote) {
	currentTime =(new Date()).getTime();
	console.log(currentTime-lastTime + "\t" +  message );
	lastTime = currentTime;
    //console.log("incoming " + remote.address + ':' + remote.port +' - ' + message);
	
	//send to 
	clients.forEach(function (client) {
		try {
			if (client.writable) {
				//id x y z
				client.write(message.toString()+"\n");
				// fs.appendFile('gameside.txt', message.toString()+"\t" + process.hrtime()+"\n", function (err) {
					// if (err) throw err;
					// currentTimeClient =(new Date()).getTime();
					// console.log((currentTimeClient-lastTimeClient) +" ms, clients " + message);
					// lastTimeClient = currentTimeClient;
					// //console.log(buf.toString()+ "\t" + process.hrtime());
					// //console.log('The "data to append" was appended to file!');
				// });
				
			} else {
				removeClient(client);
				//only on actual stopped client
				//console.log(process.hrtime()+ "\t" +'Client Removed');
			}
		} catch (err) {
			console.log("client had error" + err);
			removeClient(client);
		}
	});
});

function removeClient(c) {
  console.log("Client Lost");
  clients.splice(clients.indexOf(c), 1);
}

server.on('error', function (err) {
	console.log('UDP error '+ err);
});

//server.bind(PORT, TRACKERHOST);
server.bind(PORT);


process.on('uncaughtException', function (err) {
	console.log('UDP uncaught exception '+err);
});


