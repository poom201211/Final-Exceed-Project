// key value
let type1 = "problem"
let type2 = "level"
let type3 = "room"
let type4 = "check_empty"

//data
let problem = ''
let level = ''
let room = ''
let check_empty = ''

let getWeb = (type) => {
    $.ajax({
        type: "GET",
        url: `http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-${type}/view`,
        dataType: "text",
        success: function (response) {
            console.log(response + type)
            if (type === 'problem') {
                if (response === '1') {
                   problem = 'tissue'
                } else if (response === '2') {
                    problem = 'clog'
                } else if (response === '3') {
                    problem = 'light'
                }
            } else if (type === 'level') {
                if (response === '1') {
                    level = '1'
                } else if (response === '2') {
                    level = '2'
                }
            } else if (type === 'room') {
                if (response === '1') {
                    room = '1'
                } else if (response === '2') {
                    room = '2'
                } else if (response === '3') {
                    room = '3'
                } else if (response === '4') {
                    room = '4'
                }
            } else if (type === 'check_empty') {
                if (response === '0') {
                    check_empty = 'no'
                } else if (response === '1') {
                    check_empty = 'yes'
                }
            }

        },
        fail: function (response) {
            console.log(response)
        }
        
    });
}

let getAll = () => {
    getWeb(type1)
    getWeb(type2)
    getWeb(type3)
    getWeb(type4)
}

let sendTo = () => {
    console.log("here")
    if (problem === 'tissue'){
        $('#row1').append(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    }else if (problem === 'clog'){
        $('#row2').append(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    }else if (problem === 'light'){
        $('#row3').append(`<div class="alert alert-warning alert-dismissible fade show" role="alert">
        <h4>level: ${level} room: ${room}</h4>
        <button type="button" id="close-button" class="close" data-dismiss="alert" aria-label="Close">
        <span aria-hidden="true">&times;</span>
        </button>
        </div>`)
    }
}

let setWeb = () => {
    let stage = -1
    $('#close-button').on('click', function(){
        $('#row1').hover(function(){
            stage = 0
        })
        $('#row2').hover(function(){
            stage = 0
        })
        $('#row3').hover(function(){
            stage = 0
        })
    })


    $.ajax({
        type: "POST",
        url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
        data: {
            value: stage
        },
        dataType: "json",
        success: function (response) {
            
        }
    });
}

let init = () => {
    setInterval(getAll, 5000)
 //   setWeb()
}

$(init)