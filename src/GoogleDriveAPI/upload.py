from google.oauth2.credentials import Credentials
from google_auth_oauthlib.flow import InstalledAppFlow
from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload
import os

SCOPES = [
    'https://www.googleapis.com/auth/drive.file',
    'https://www.googleapis.com/auth/spreadsheets'
]


def upload_csv_and_create_line_chart(file_path, file_name, chart_config=None):
    if os.path.exists('token.json'):
        creds = Credentials.from_authorized_user_file('token.json', SCOPES)

    else:
        flow = InstalledAppFlow.from_client_secrets_file('credentials.json', SCOPES)
        creds = flow.run_console()
        with open('token.json', 'w') as token:
            token.write(creds.to_json())

    drive_service = build('drive', 'v3', credentials=creds)
    sheets_service = build('sheets', 'v4', credentials=creds)

    file_metadata = {
        'name': file_name,
        'mimeType': 'text/csv' if chart_config is None else 'application/vnd.google-apps.spreadsheet',
        'parents': ['1T-YZCDF8s7xgbjPU_NZG6vI2AC-ap1G5']
    }

    media = MediaFileUpload(file_path, mimetype='text/csv')
    file = drive_service.files().create(
        body=file_metadata,
        media_body=media,
        fields='id'
    ).execute()

    spreadsheet_id = file.get('id')
    print(f"Uploaded {'csv' if chart_config is None else 'spreadsheet'} with ID: {spreadsheet_id}")

    if chart_config is not None:
        spreadsheet = sheets_service.spreadsheets().get(spreadsheetId=spreadsheet_id).execute()
        sheet_id = spreadsheet['sheets'][0]['properties']['sheetId']
        print(f"Sheet ID of the first sheet: {sheet_id}")

        requests = [
            {
                "addChart": {
                    "chart": {
                        "spec": {
                            "title": chart_config["title"],
                            "basicChart": {
                                "chartType": "LINE",
                                "lineSmoothing": chart_config["smooth"],
                                "legendPosition": "BOTTOM_LEGEND",
                                "axis": [
                                    {"position": "BOTTOM_AXIS", "title": chart_config["x_axis"]},
                                    {"position": "LEFT_AXIS", "title": chart_config["y_axis"]}
                                ],
                                "domains": [
                                    {
                                        "domain": {
                                            "sourceRange": {
                                                "sources": [
                                                    {
                                                        "sheetId": sheet_id,  # use real sheetId here
                                                        "startRowIndex": 0,
                                                        "endRowIndex": 11,
                                                        "startColumnIndex": 0,
                                                        "endColumnIndex": 1
                                                    }
                                                ]
                                            }
                                        }
                                    }
                                ],
                                "series": [
                                    {
                                        "series": {
                                            "sourceRange": {
                                                "sources": [
                                                    {
                                                        "sheetId": sheet_id,  # use real sheetId here
                                                        "startRowIndex": 0,
                                                        "endRowIndex": 11,
                                                        "startColumnIndex": 1,
                                                        "endColumnIndex": 2
                                                    }
                                                ]
                                            }
                                        },
                                        "targetAxis": "LEFT_AXIS"
                                    }
                                ],
                                "headerCount": 1
                            }
                        },
                        "position": {
                            "newSheet": True
                        }
                    }
                }
            }
        ]

        body = {'requests': requests}

        sheets_service.spreadsheets().batchUpdate(
            spreadsheetId=spreadsheet_id,
            body=body
        ).execute()

        print("Chart created successfully")


chart_config = {
    "title": "X vs Y",
    "x_axis": "x axis",
    "y_axis": "y axis",
    "smooth": True
}

upload_csv_and_create_line_chart('test.csv', 'test_raw')
upload_csv_and_create_line_chart('test.csv', 'test', chart_config)
