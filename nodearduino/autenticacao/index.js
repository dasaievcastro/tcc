      var Usuarios = require('../models/Usuario')

      function Autenthicate(passport,LocalStrategy,db){
        var usuario = new Usuarios(db);

        //   passport.use(new WindowsStrategy({ 
        //   ldap: {
        //     url:             'ldap://192.168.201.210/DC=gama,DC=rede',
        //     base:            'DC=gama,DC=rede',
        //     bindDN:          'dasaiev.castro@gama.rede',
        //     bindCredentials: '123456'
        //   },
        //   integrated:      false
        //   }, function(profile, done){
        //     if(profile){
        //       var user={};
        //     user.senha ='123456'
        //     user.name = profile._json.givenName
        //     user.id = profile.id
        //     done(null, user);
        //   }else{
        //     done(null,false);
        //   }
        // }));
        passport.use(new LocalStrategy(
          function(username, password, done) {
            usuario.findOne({ username: username, password:password }, function(err, user) {
              if (err) { return done(err); }
              if (!user) {
                return done(null, false);
              }
              return done(null, user);
            });
          }
        ))
        passport.serializeUser(function(user, done) {
          done(null, user);
        });

        passport.deserializeUser(function(obj, done) {
          done(null, obj);
        });

    }

    module.exports = Autenthicate;