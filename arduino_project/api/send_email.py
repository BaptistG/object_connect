from .config import smtp_server, sender_email, password, receiver_email

import smtplib, ssl
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import json
from datetime import datetime,date
import time

def notify_user(username, address):



    port = 465  # For SSL

    message = MIMEMultipart("alternative")
    message["Subject"] = "{} est en danger!".format(username)
    message["From"] = sender_email
    message["To"] = receiver_email

    trip_html = ""



    # Create the plain-text and HTML version of your message
    text = """\
    Bonjour,

    Il faut vite aller sauver {0} a l'adresse suivante: {1}

    Cordialement,
    L'équipe NannySavior""".format(username, address)

    html = """
    <!doctype html>
    <html>
    <body>
    Bonjour,

    Il faut vite aller sauver {0} a l'adresse suivante: {1}

    Cordialement,
    L'équipe NannySavior
    </body>
    </html>""".format(username, address)

    # html = email_template.rstrip("\n").format(username, trip['departure'], trip['arrival'], trip['date'], trip_html.rstrip("\n"))
    # Turn these into plain/html MIMEText objects
    part1 = MIMEText(text, "plain")
    part2 = MIMEText(html, "html")

    # Add HTML/plain-text parts to MIMEMultipart message
    # The email client will try to render the last part first
    message.attach(part1)
    message.attach(part2)

    # Create secure connection with server and send email
    context = ssl.create_default_context()
    with smtplib.SMTP_SSL(smtp_server, port, context=context) as server:
        server.login(sender_email, password)
        server.sendmail(
            sender_email, receiver_email, message.as_string()
        )
        print("Sent email to {}".format(username))
