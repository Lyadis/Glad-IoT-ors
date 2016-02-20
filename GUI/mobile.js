/* Page logic */
$(document).ready(function() {
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
  
  var score = $('span#score');
  var hits = $('span#score');
  
  var startShooter = function(ip,id) {
    shooterMsgOnConnect = function() {
      $('div#teamchooser').css('display','none');
      $('div#buttons').css('display','inherit');
      // Change status updates
      thingmlMessages.recieve = function(sid,registered,score,shots,hits) {
        if (sid == id) {
          if (registered) {
            score.html(score);
            hits.html(hits);
          } else {
            location.reload();
          }
        }
      };
    };
    connectShooter(ip);
  };
  
  /* Start by getting list of teams currently */
  $('div#teamchooser').css('display','inherit');
  var colors = ['red','blue','yellow','green','orange','cyan','magenta'];
  
  /* List teams */
  var teams = [];
  var container = $('div#teamlist');
  var template = $('div#team-0');
  thingmlMessages.recieve.teamStatus = function(id,registered,score,shots,hits,ip) {
    if (teams[id]) {
      var team = teams[id];
      // Update
      if (!registered) {
        team.el.remove();
        teams[id] = undefined;
      }
    } else {
      if (registered) {
        // Create
        var team = {};
        team.el = template.clone();
        team.el.attr('id','team-'+id);
        team.el.find('h2').html('Team '+id);
        team.el.find('div.color').css('background-color',colors[id-1 % colors.length]);

        team.el.click(function() {
          ip = '10.59.11.83';
          startShooter(ip,id);
        });

        teams[id] = team;
        container.append(team.el);
      }
    }
  }
  // Get list when ready
  thingmlMessages.send.listStatuses();
  msgOnConnect = function() { thingmlMessages.send.listStatuses(); };
  
  
  

  thingmlMessages.recieve.gameStatus = function(running) {
    console.log("Game running: "+running);
  };
  
  thingmlMessages.recieve.secondsLeft = function(s) {
    console.log("Seconds left: "+s);
  };
});