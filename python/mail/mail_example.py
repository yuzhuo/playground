#!/usr/bin/python
#-*- encoding: utf8 -*-


from datetime import date, timedelta
import smtplib
from email.mime.text import MIMEText
from email.header import Header
import socket


def get_html():
    html = '<html><body><h1>Hello, world!</h1></body></html>'
    return html


def send_mail(html):
    receivers = ['goodcomrade@hotmail.com']

    html = '<p>主机：%s</p><p></p>' % socket.gethostname() + html
    msg = MIMEText(html, 'html', 'utf8')
    msg['Subject'] = Header("i'm header", 'utf8')
    msg['From'] = '%s' % socket.gethostname()
    msg['To'] = ','.join(receivers)
    msg["Accept-Language"]="zh-CN"
    msg["Accept-Charset"]="ISO-8859-1,utf-8"

    s = smtplib.SMTP('mxbiz1.qq.com')
    s.sendmail('goodcomrade@hotmail.com', receivers, msg.as_string())
    s.quit()


def main():
    html = get_html()
    send_mail(html)
    print 'send!'

if __name__ == '__main__':
    main()


