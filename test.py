
import tabula

# Extract tables from all pages of the PDF and save to CSV
pdf_path = "input.pdf"
output_csv = "output.csv"
tabula.convert_into(pdf_path, output_csv, output_format="csv", pages="all")

print(f"Tables extracted to {output_csv}")
