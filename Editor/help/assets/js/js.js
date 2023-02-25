$('p').after('<div class="divider"></div>');
// $('h3').before('<div class="divider"></div>');


$(function()
{
    var offset = -78;
    var scrollTime = 500;
    $('a[href^="#"]').click(function()
    {
        $("html, body").animate({
            scrollTop: $( $(this).attr("href") ).offset().top + offset 
        }, scrollTime);
        return false;
    });
});