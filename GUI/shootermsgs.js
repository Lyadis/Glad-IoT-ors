var shooterMsgSend = function() {};

/* ThingML encoding/decoding */
var shooterMessages = {
  recieve: {
    'ready': function() {},
    'beenHit': function(shooter) {}
  },
  send: {
    'shootCmd': function(id) {
      window.shooterMsgSend('000201'+(id < 100 ? '0' : '')+(id < 10 ? '0' : '') + id);
    }
  }
};

var decodeShooterMsg = function(msg) {
  var code = msg.substring(0,6);
  var params = msg.substring(6);
  
  switch (code) {
    case '000200':
      shooterMessages.recieve.ready();
      break;
    case '000202':
      var shooter = parseInt(params.substring(0,3));
      shooterMessages.recieve.beenHit(shooter);
      break;
    default:
      console.log('Unhandled message:', code, params);
  }
};

/* Start WebSocket connection */
var connectShooter = function(ip) {
  var socket;
  var start = function() {
    socket = new WebSocket('ws://'+ip+':9000','ThingML-protocol');
    socket.onopen = function() {
      console.log('Opened...');
      shooterMsgSend = function(msg) { socket.send(msg); };
    };
    socket.onmessage = function(msg) { decodeShooterMsg(msg.data); };
    socket.onclose = function() {
      shooterMsgSend = function() {};
      start();
    };
  };
  start();
};