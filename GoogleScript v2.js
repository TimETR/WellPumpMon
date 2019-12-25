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

pumpId
state
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
      var id = '1JssIrz_73HwOobljvRGWAc1hn-fMd5o31thbOUmIjSc';//docs.google.com/spreadsheetURL/d
      var sheet = SpreadsheetApp.openById(id).getActiveSheet();
      var newRow = sheet.getLastRow() + 1;
      var rowData = [];
      //var waktu = new Date();
      rowData[0] = new Date().toDateString(); // Date in column A
      rowData[1] = new Date().toLocaleTimeString(); //Time in column B
      for (var param in e.parameter) {
        Logger.log('In for loop, param='+param);
        var value = stripQuotes(e.parameter[param]);
        Logger.log(param + ':' + e.parameter[param]);
        switch (param) {
          case 'pumpid': //Parameter
            rowData[2] = value; //Value in column C
            break;
          case 'state':
            rowData[3] = value; //Value in column D
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