from googleapiclient.discovery import build
from googleapiclient.http import MediaFileUpload
from google.oauth2 import service_account
import csv

SCOPES = [
    'https://www.googleapis.com/auth/drive.file',
    'https://www.googleapis.com/auth/spreadsheets'
]

def get_rows(file_path):
    with open(file_path, 'r') as f:
        reader = csv.reader(f)
        row_count = sum(1 for row in reader)
    return row_count - 1


def upload_csv_and_create_line_chart(file_path, file_name, chart_config=None):
    SERVICE_ACCOUNT_FILE = 'service.json'

    creds = service_account.Credentials.from_service_account_file(
        SERVICE_ACCOUNT_FILE, scopes=SCOPES)

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

        rows = get_rows(file_path)

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
                                                        "endRowIndex": rows,
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
                                                        "endRowIndex": rows,
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
