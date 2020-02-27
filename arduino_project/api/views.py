# -*- coding: utf-8 -*-
from __future__ import unicode_literals
from django.shortcuts import render
from django.views.generic import TemplateView

from rest_framework.response import Response
from rest_framework.views import APIView

from .models import Alerts, Users
from .serializers import AlertsSerializer

class HomeView(TemplateView):
    template_name = 'index.html'

    def get_context_data(self, **kwargs):
        context = super(HomeView, self).get_context_data(**kwargs)
        users = Users.objects.all()
        alerts = Alerts.objects.all()

        res = {}

        for row in users:
            res[row.username] = 0
            for r in alerts:
                if str(row.id) == str(r.user_id):
                    res[row.username] += 1

        alerts_users = ""
        alerts_count = ""
        for username, count in res.items():
            alerts_users += "{},".format(username)
            alerts_count += "{},".format(count)

        alerts_users = alerts_users[:-1]
        alerts_count = alerts_count[:-1]

        context["alerts_users"] = alerts_users
        context["alerts_count"] = alerts_count
        return context

class AlertsView(APIView):
    """
    Provides a get method handler.
    """
    def get(self, request):
        alerts = Alerts.objects.all()
        serializer = AlertsSerializer(alerts, many=True)
        return Response({'alerts': serializer.data})

    def post(self, request):
        alert = request.data.get('alert')
        username = alert.get('username')
        user = Users.objects.filter(username=username).first()

        if not user:
            return Response({"success": "User not found"})

        data = {
            'user_id': user.id
        }

        # Create an article from the above data
        serializer = AlertsSerializer(data=data)

        if serializer.is_valid(raise_exception=True):
            alert_saved = serializer.save()
        return Response({"success": "Alert for {} created successfully".format(username)})
