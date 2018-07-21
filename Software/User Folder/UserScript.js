
let myFunction = function () {
    let start = '../Pictures/Room Free.png'
    let error = '../Pictures/Room Error.png'
    let free = '../Pictures/Room Free.png'
    let used = '../Pictures/Room Used.png'

    setInterval(function () {
        $.ajax({
            type: "GET",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/view",
            dataType: "text",
            success: function (response) {
                $('Room1').attr("src",start)
                
            },
            fail: function (response) {
                console.log(response)
            }
            
        });

        $.ajax({
            type: "GET",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/view",
            dataType: "text",
            success: function (response) {
                $('Room2').attr("src",start)
                
            },
            fail: function (response) {
                console.log(response)
            }
            
        });

        $.ajax({
            type: "GET",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/view",
            dataType: "text",
            success: function (response) {
                $('Room3').attr("src",start)
                
            },
            fail: function (response) {
                console.log(response)
            }
            
        });

        $.ajax({
            type: "GET",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/view",
            dataType: "text",
            success: function (response) {
                $('Room4').attr("src",start)
                
            },
            fail: function (response) {
                console.log(response)
            }
            
        });
    }, 5000)
}


$(myFunction)