import smtplib

# Import the email modules we'll need
from email.mime.text import MIMEText

# Open a plain text file for reading.  For this example, assume that
# the text file contains only ASCII characters.
textfile = "test"
fp = open(textfile, 'rb')
# Create a text/plain message
msg = MIMEText(fp.read())
fp.close()

# me == the sender's email address
# you == the recipient's email address
msg['Subject'] = 'date'
msg['From'] = 'jiutong'
msg['To'] = 'lily'

# Send the message via our own SMTP server, but don't include the
# envelope header.
s = smtplib.SMTP('mxbiz1.qq.com')
s.sendmail('jiutong@jiutong.com', ['goodcomrade@hotmail.com'], msg.as_string())
s.quit()
