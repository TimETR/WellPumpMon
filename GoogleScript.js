//-----------------------------------------------
//Originally published by Mogsdad@Stackoverflow
//Modified for jarkomdityaz.appspot.com
//Modified for Hackster.io by Stephen Borsay
//-----------------------------------------------
/*

GET request query:

https://script.google.com/macros/s/<gscript id>/exec?celData=data_here
----------------------------------------------------------------------

GScript, PushingBox and Arduino/ESP8266 Variables in order:

humidityDat
celData
fehrData
hicData
hifData
----------------------------------------------------
*/


/* Using spreadsheet API */

function doGet(e) { 
    Logger.log( JSON.stringify(e) );  // view parameters
  
    var result = 'Ok'; // assume success
  
    if (e.parameter == undefined) {
      result = 'No Parameters';
    }
    else {
      var id = '<YOUR_SPREADSHEET_URL_HERE';//docs.google.com/spreadsheetURL/d
      var sheet = SpreadsheetApp.openById(id).getActiveSheet();
      var newRow = sheet.getLastRow() + 1;
      var rowData = [];
      //var waktu = new Date();
      rowData[0] = new Date(); // Timestamp in column A
      
      for (var param in e.parameter) {
        Logger.log('In for loop, param='+param);
        var value = stripQuotes(e.parameter[param]);
        //Logger.log(param + ':' + e.parameter[param]);
        switch (param) {
          case 'humidityData': //Parameter
            rowData[1] = value; //Value in column B
            break;
          case 'celData':
            rowData[2] = value;
            break;
          case 'fehrData':
            rowData[3] = value;
            break;
          case 'hicData':
            rowData[4] = value;
            break;
          case 'hifData':
            rowData[5] = value;
            break;
          default:
            result = "unsupported parameter";
        }
      }
      Logger.log(JSON.stringify(rowData));
  
      // Write new row below
      var newRange = sheet.getRange(newRow, 1, 1, rowData.length);
      newRange.setValues([rowData]);
    }
  
    // Return result of operation
    return ContentService.createTextOutput(result);
  }
  
  /**
  * Remove leading and trailing single or double quotes
  */
  function stripQuotes( value ) {
    return value.replace(/^["']|['"]$/g, "");
  }