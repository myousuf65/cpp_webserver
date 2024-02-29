### LOGIN

<aside>
💡 Endpoint : POST `/api/login`  HTTP 1.1

</aside>

```jsx
{
	"username" : "__username__",
	"password" : "__password__",
	"email" : "__email__"
}
```

<br><br>
### POST A RECORD OF STUDENT

<aside>
💡 Endpoint : POST `/api/post`  HTTP 1.1
</aside>

```jsx
{
	"u:id" : __id__,
	"firstName" : "__firstname__",
	"lastName" : "__lastname__",
	"emailAddress" : "__email__",
	"phone" : __phone__
}
```
<br><br>
### GET ALL STUDENTS

<aside>
💡 Endpoint : GET `/api/get` HTTP 1.1

</aside>

<br><br>
### UPDATE A  STUDENT RECORD

<aside>
💡 Endpoint : PUT`/api/get` HTTP 1.1
</aside>

<br><br>
### DELETE A  STUDENT RECORD

<aside>
💡 Endpoint : PUT`/api/delete` HTTP 1.1
</aside>

```jsx
{
	"u:id" : __id__
}
```
