/* Page logic */
$(document).ready(function() {
  $('div#buttons').css('display','inherit');
  
  /* Set up shooting */
  $('button#button').click(function() {
    shooterMessages.send.shootCmd(0);
  });
  shooterMessages.recieve.beenHit = function(shooter) {
    $('div#hit').css('display','inherit');
    setTimeout(function() {
      $('div#hit').css('display','none');
    },1000);
  };
  
  /* Start by getting list of teams currently */
  //$('div#teamchooser').css('display','inherit');
  thingmlMessages.recieve.teamStatus = function(id,registered,score,shots,hits,ip) {
    console.log('Status:',id,registered,score,shots,hits,ip);
  };
  
  
  

  thingmlMessages.recieve.gameStatus = function(running) {
    console.log("Game running: "+running);
  };
  
  thingmlMessages.recieve.secondsLeft = function(s) {
    console.log("Seconds left: "+s);
  };
  
  thingmlMessages.recieve.teamStatus = function(id,registered,score,shots,hits,ip) {
    console.log('Status:',id,registered,score,shots,hits,ip);
  };
  
  connectShooter('10.59.2.65');
});