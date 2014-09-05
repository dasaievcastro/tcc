var express = require('express.io')
,	app = express()
,	passport = require('passport')
, 	ejs = require('ejs')
, 	flash = require('connect-flash')
,	mongoClient = require('mongodb').MongoClient
,	rotas = require('./rotas')
,	localStrategy = require('passport-local').Strategy
,	autenticacao = require('./autenticacao');

app.http().io();
app.configure(function() {
	app.use(express.compress());
    app.set('view engine', 'ejs');
	app.use(express.static(__dirname + '/public'));
	app.set('views', __dirname + '/views');
	app.use(express.cookieParser());
	app.use(express.bodyParser());
	app.use(express.session({ secret: 'hashdesegurancaprojetoarduino' }));
	app.use(flash());
    app.use(passport.initialize());
    app.use(passport.session());
});

mongoClient.connect('mongodb://127.0.0.1:27017/aplicacao', function(err, db) {
autenticacao(passport,localStrategy,db);
rotas(app,db,passport);

});

app.listen(8086);
