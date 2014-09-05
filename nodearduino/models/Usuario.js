
/* The ContentHandler must be constructed with a connected db */
function Usuarios(db) {
    "use strict";
    var Usuario = db.collection('usuario');
    var classe = 'Usuario';
    this.index = function(req, res) {

        //res.render('cargos/index',{title:classe,cargos:cargos});
    }

    this.findOne = function(user,callback){
        Usuario.find({login:user.username,senha:user.password}).toArray(function(err,resp){
            if(err) throw err;
            if(resp.length==1){
                callback('',resp);
            }else{
                callback('usuário não encontrado','');
            }
        })
    }

    
}

module.exports = Usuarios;
