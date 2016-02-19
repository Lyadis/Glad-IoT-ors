/* Page logic */
$(document).ready(function() {
  var time = $('span#time');
  thingmlMessages.recieve.secondsLeft = function(secs) {
    var min = Math.floor(secs/60);
    var sec = secs-min*60;
    var str = (min < 10 ? '0' : '') + min + ':' + (sec < 10 ? '0' : '') + sec;
    time.html(str);
  };
});