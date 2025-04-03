import requests
import pandas as pd

# Define your domain
domain = "https://dev-xyz-uk.tesapps.test"

# Read source paths from Excel
def read_source_path(file_path, sheet_name="Sheet1"):
    df = pd.read_excel(file_path, sheet_name=sheet_name)
    return df['Source Path'].tolist()

# Function to check redirects
def check_redirects(source_path):
    results = []
    
    for path in source_path:
        url = f"{domain}{path}"
        try:
            response = requests.get(url, allow_redirects=False)
            status_code = response.status_code
            location = response.headers.get("Location", "No Redirect")
            
            results.append({
                "Source Path": path,
                "Status Code": status_code,
                "Redirect Location": location if status_code == 301 else "N/A"
            })
            
        except requests.RequestException as e:
            results.append({
                "Source Path": path,
                "Status Code": "Error",
                "Redirect Location": str(e)
            })
    
    return results

# Save results to an Excel file
def save_results_to_excel(results, output_file):
    df = pd.DataFrame(results)
    df.to_excel(output_file, index=False)

if __name__ == "__main__":
    input_file = "source_path.xlsx"  # Change this to your input file
    output_file = "redirect_results.xlsx"
    
    source_path = read_source_path(input_file)
    results = check_redirects(source_path)
    save_results_to_excel(results, output_file)
    
    print(f"Results saved to {output_file}")
