var msgSend = function() {};
var msgOnConnect = function() {};

/* ThingML encoding/decoding */
var thingmlMessages = {
  recieve: {
    'gameStatus': function(running) {},
    'secondsLeft': function(secs) {},
    'teamStatus': function(id,registered,score,shots,hits,ip) {}
  },
  send: {
    'getGameStatus': function() {
      window.msgSend('000153');
    },
    'listStatuses': function() {
      window.msgSend('000152');
    },
    'gameStart': function() {
      window.msgSend('000150');
    },
    'gameStop': function() {
      window.msgSend('000151');
    }
  }
};

var decodeThingmlMsg = function(msg) {
  var code = msg.substring(0,6);
  var params = msg.substring(6);
  
  switch (code) {
    case '000154':
      thingmlMessages.recieve.gameStatus(params.substring(0,3) != '000');
      break;
    case '000155':
      var secs = parseInt(params.substring(0,3))*256+parseInt(params.substring(3,6));
      thingmlMessages.recieve.secondsLeft(secs);
      break;
    case '000156':
      var id = parseInt(params.substring(0,3));
      var registered = params.substr(3,6) != '000';
      var score = parseInt(params.substring(6,9))*256+parseInt(params.substring(9,12));
      var shots = parseInt(params.substring(12,15))*256+parseInt(params.substring(15,18));
      var hits = parseInt(params.substring(18,21))*256+parseInt(params.substring(21,24));
      var ip = params.substring(24,27)+'.'+params.substring(27,30)+'.'+params.substring(30,33)+'.'+params.substring(33,36);
      thingmlMessages.recieve.teamStatus(id,registered,score,shots,hits,ip);
      break;
    default:
      console.log('Unhandled message:', code, params);
  }
};

/* Start WebSocket connection */
(function() {
  var socket;
  var start = function() {
    socket = new WebSocket('ws://10.59.10.3:9000','ThingML-protocol');
    socket.onopen = function() {
      msgSend = function(msg) { socket.send(msg); };
      msgOnConnect();
    };
    socket.onmessage = function(msg) { decodeThingmlMsg(msg.data); };
    socket.onclose = function() {
      msgSend = function() {};
      start();
    };
  };
  start();
})();