var express = require('express.io');
app = express();
app.http().io()

// Setup the ready route, and emit talk event.


app.use(express.static(__dirname + '/public'));

app.io.route('rotapadrao', function(req) {
	var led = String(req.data.led);
	//console.log(ligado);
    //req.io.emit('rotaenviousuario', {
      //  'felipe': 'meu nome é felipe',
       // 'dasaiev': 'meu nome é dasaiev'
    //})
	console.log(led);
	app.io.broadcast(led);
})


app.io.on('connection',function(socket){
	//monitora qualquer mensagem enviada pelo arduíno...
	socket.on('message',function(data){
		console.log(data);
		app.io.broadcast('rotaenviousuario',{
			led:data
    	})
		
	})

})



// Send the client html.
app.get('/', function(req, res) {
    res.sendfile(__dirname + '/bootstrap.html')
})

app.get('/app2', function(req, res) {
    res.sendfile(__dirname + '/client.html')
})


app.listen(8087)
