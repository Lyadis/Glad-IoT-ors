/* Page logic */
$(document).ready(function() {
  var time = $('span#time');
  thingmlMessages.recieve.secondsLeft = function(secs) {
    var min = Math.floor(secs/60);
    var sec = secs-min*60;
    var str = (min < 10 ? '0' : '') + min + ':' + (sec < 10 ? '0' : '') + sec;
    time.html(str);
  };
  
  var colors = ['red','blue','yellow','green','orange','cyan','magenta'];
  
  /* Team list */
  var teams = [];
  var container = $('div#teamlist');
  var template = $('div#team-0');
  thingmlMessages.recieve.teamStatus = function(id,registered,score,shots,hits) {
    if (teams[id]) {
      var team = teams[id];
      // Update
      if (registered) {
        team.success.html( (score<10?'0':'')+score );
        team.hits.html( (hits<10?'0':'')+hits );
        team.accuracy.html( Math.round(shots > 0 ? score/shots*100 : 100)+'%' );
      } else {
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

        team.success = team.el.find('span.success').html('00');
        team.hits = team.el.find('span.hits').html('00');
        team.accuracy = team.el.find('div.accuracy span').html('100%');

        teams[id] = team;
        container.append(team.el);
      }
    }
  }
  // Get list when ready
  thingmlMessages.send.listStatuses();
  msgOnConnect = function() { thingmlMessages.send.listStatuses(); };
});