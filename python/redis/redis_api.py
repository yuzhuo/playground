#!/usr/bin/env python2.6
#-*- coding:utf-8 -*-

import redis

def func_status(func):
    def _func_status(*args, **kwargs):
        error, result = None, None
        try:
            result = func(*args, **kwargs)
        except Exception as e:
            error = str(e)

        return {'result': result, 'error': error}

    return _func_status

class redis_conn:
    def __init__(self, host, password, port = 6379, db = 1):
        self.pool = redis.ConnectionPool(host = host, port = port,
                                password = password, db = db)

        self.connection = redis.StrictRedis(connection_pool = self.pool)

    @func_status
    def _set_key(self, key, value, ex=None):
        return self.connection.set(key, value, ex)

    def set_key(self, key, value, ex=None):
        res = self._set_key(key, value, ex)
        if res['error']:
            print 'Set "{0}" to "{1}" failed with "{2}"'.format(key, value, res['error'])
            return 1

        return 0 if res['result'] else 1

    @func_status
    def _get_key(self, key):
        return self.connection.get(key)

    def get_key(self, key):
        res = self._get_key(key)
        if res['error']:
            print 'Get value for "{0}" failed with "{1}"'.format(key, res['error'])
            return 1, None

        if res['result'] == None:
            print 'Cannot find key "{0}"'.format(key)
            return 1, None

        return 0, res['result']

    @func_status
    def _ttl(self, key):
        return self.connection.ttl(key)

    def ttl(self, key):
        res = self._ttl(key)
        if res['error']:
            print 'Get ttl for "{0}" failed with "{1}"'.format(key, res['error'])
            return 1, None

        return 0, res['result']

    @func_status
    def _del_key(self, key):
        return self.connection.delete(key)

    def del_key(self, key):
        res = self._del_key(key)
        if res['error']:
            print 'Delete key "{0}" failed with "{1}"'.format(key, res['error'])
            return 1

        return 0 if res['result'] > 0 else 1

    @func_status
    def _incr(self, key, amount):
        return self.connection.incr(key, amount)

    def incr(self, key, amount = 1):
        res = self._incr(key, amount)
        if res['error']:
            print 'Incr key "{0}" failed with "{1}"'.format(key, res['error'])
            return 1, None

        return 0, res['result']

    @func_status
    def _lrem(self, name, count, value):
        return self.connection.lrem(name, count, value)

    def lrem(self, name, count, value):
        res = self._lrem(name, count, value)
        if res['error']:
            print 'lrem key "{0}" failed with "{1}"'.format(key, res['error'])
            return 1, None

        return 0, res['result']

    def scan(self, cursor = 0, match = None, count = None):
        return self.connection.scan(cursor, match, count)

    def strlen(self, key):
        return self.connection.strlen(key)

if '__main__' == __name__:
    redis_obj = redis_conn(host = '192.168.1.3', port = 6379, password = '', db = 1)
    print redis_obj.set_key('Testkey', "Simple Test")
    print redis_obj.get_key('Testkey')

