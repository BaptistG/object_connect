from django.db import models

# Create your models here.
class Alerts(models.Model):
    id = models.AutoField(primary_key=True)
    user_id = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return 'id: {}, user: {}'.format(self.id, self.user_id)

class Users(models.Model):
    id = models.AutoField(primary_key=True)
    username = models.TextField()
    address = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return 'id: {}, username: {}'.format(self.id, self.username)
