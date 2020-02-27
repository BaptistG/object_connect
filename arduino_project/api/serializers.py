from rest_framework import serializers
from .models import Alerts


# class AlertsSerializer(serializers.ModelSerializer):
#     class Meta:
#         model = Alerts
#         fields = ("username")

class AlertsSerializer(serializers.Serializer):
    user_id = serializers.CharField()

    def create(self, validated_data):
        return Alerts.objects.create(**validated_data)
