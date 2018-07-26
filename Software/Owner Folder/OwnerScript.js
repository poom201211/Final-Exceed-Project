// key value
let type1 = "problem"
let type2 = "level"
let type3 = "room"
let type4 = "sos_room"
let type5 = "sos_level"

//data
let problem = 0
let level = 0
let room = 0
let check_empty = 0
let sosRoom = 0
let sosLevel = 0

let getWeb = (type) => {
    $.ajax({
        type: "GET",
        url: `http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-${type}/view`,
        dataType: "text",
        success: function (response) {
            if (type === 'problem') {
                if (response === '0') {
                    problem = 0
                }
                if (response === '1') {
                    problem = 'tissue'
                } if (response === '2') {
                    problem = 'clog'
                } if (response === '3') {
                    problem = 'light'
                }
            } else if (type === 'level') {
                if (response === '1') {
                    level = 1
                } else if (response === '2') {
                    level = 2
                }
            } else if (type === 'room') {
                if (response === '1') {
                    room = 1
                } else if (response === '2') {
                    room = 2
                } else if (response === '3') {
                    room = 3
                } else if (response === '4') {
                    room = 4
                }
            } else if (type === 'sos_room') {
                if (response === '0') {
                    sosRoom = 0
                }
                if (response === '1') {
                    sosRoom = 1
                    callSOS()
                }
                if (response === '2') {
                    sosRoom = 2
                }
                if (response === '3') {
                    sosRoom = 3
                }
                if (response === '4') {
                    sosRoom = 4
                }
            } else if (type === 'sos_level') {
                if (response === '1') {
                    sosLevel = 1
                } else if (response === '2') {
                    sosLevel = 2
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
    getWeb(type5)

    sendTo()
}

let callSOS = () => {
    $('#SOS').html(`<div style="background-color: red">level: ${sosLevel} room: ${sosRoom}</div>`)
}

let sendTo = () => {
    if (problem === 'tissue') {
        console.log("h1")
        $(`#1row${level}_${room}`).html(`level:${level} room:${room}`)
    } else if (problem === 'clog') {
        console.log("h2")
        $(`#2row${level}_${room}`).html(`level:${level} room:${room}`)
    } else if (problem === 'light') {
        console.log("h3")
        $(`#3row${level}_${room}`).html(`level:${level} room:${room}`)
    }

}

let setup = () => {
    $('#sos-button').on('click', function () {
        $('#SOS').html(`<div>No Signal</div>`)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-sos_room/set",
            data: {
                value: 0
            },
            dataType: "text",
            success: function (response) {

            }
        });
    })

    sosRoom = 0

    $('#1row1_1').on('click', function () {
        $('#1row1_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row1_2').on('click', function () {
        $('#1row1_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row1_3').on('click', function () {
        $('#1row1_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row1_4').on('click', function () {
        $('#1row1_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row2_1').on('click', function () {
        $('#1row2_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row2_2').on('click', function () {
        $('#1row2_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row2_3').on('click', function () {
        $('#1row2_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#1row2_4').on('click', function () {
        $('#1row2_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row1_1').on('click', function () {
        $('#2row1_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row1_2').on('click', function () {
        $('#2row1_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row1_3').on('click', function () {
        $('#2row1_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row1_4').on('click', function () {
        $('#2row1_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row2_1').on('click', function () {
        $('#2row2_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row2_2').on('click', function () {
        $('#2row2_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row2_3').on('click', function () {
        $('#2row2_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#2row2_4').on('click', function () {
        $('#2row2_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row1_1').on('click', function () {
        $('#3row1_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row1_2').on('click', function () {
        $('#3row1_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row1_3').on('click', function () {
        $('#3row1_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row1_4').on('click', function () {
        $('#3row1_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row2_1').on('click', function () {
        $('#3row2_1').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row2_2').on('click', function () {
        $('#3row2_2').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row2_3').on('click', function () {
        $('#3row2_3').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

    $('#3row2_4').on('click', function () {
        $('#3row2_4').html(``)
        $.ajax({
            type: "POST",
            url: "http://ecourse.cpe.ku.ac.th/exceed/api/buapalm-problem/set",
            data: {
                value: "0"
            },
            dataType: "text",
            success: function (response) {
                console.log(12345)
            }
        });
    })

    problem = 0

}

let init = () => {
    setup()
    setInterval(getAll, 5000)
}

$(init)