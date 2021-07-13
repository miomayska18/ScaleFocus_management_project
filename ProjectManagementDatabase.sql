USE [ProjectManagement]
GO
/****** Object:  Database [ProjectManagement]    Script Date: 7/13/2021 3:40:46 PM ******/
CREATE DATABASE [ProjectManagement]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'ProjectManagement', FILENAME = N'C:\Users\miomayska18\ProjectManagement.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'ProjectManagement_log', FILENAME = N'C:\Users\miomayska18\ProjectManagement_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [ProjectManagement].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [ProjectManagement] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [ProjectManagement] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [ProjectManagement] SET ARITHABORT OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [ProjectManagement] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [ProjectManagement] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [ProjectManagement] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [ProjectManagement] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [ProjectManagement] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [ProjectManagement] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [ProjectManagement] SET  DISABLE_BROKER 
GO
ALTER DATABASE [ProjectManagement] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [ProjectManagement] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [ProjectManagement] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [ProjectManagement] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [ProjectManagement] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [ProjectManagement] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [ProjectManagement] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [ProjectManagement] SET RECOVERY SIMPLE 
GO
ALTER DATABASE [ProjectManagement] SET  MULTI_USER 
GO
ALTER DATABASE [ProjectManagement] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [ProjectManagement] SET DB_CHAINING OFF 
GO
ALTER DATABASE [ProjectManagement] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [ProjectManagement] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [ProjectManagement] SET DELAYED_DURABILITY = DISABLED 
GO
USE [ProjectManagement]
GO
/****** Object:  Table [dbo].[Logs]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Logs](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserId] [int] NOT NULL,
	[TimeSpent] [int] NOT NULL,
	[Date] [date] NOT NULL,
	[TaskId] [int] NOT NULL,
 CONSTRAINT [PK_Log] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Projects]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Projects](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Name] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](150) NOT NULL,
	[OwnerId] [int] NOT NULL,
	[DateCreation] [datetime] NOT NULL,
	[IdCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
 CONSTRAINT [PK_Project] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[ProjectsTeams]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[ProjectsTeams](
	[ProjectId] [int] NOT NULL,
	[TeamsId] [int] NOT NULL,
 CONSTRAINT [PK_ProjectsTeams] PRIMARY KEY CLUSTERED 
(
	[ProjectId] ASC,
	[TeamsId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Tasks]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Tasks](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[Title] [nvarchar](50) NOT NULL,
	[Description] [nvarchar](150) NOT NULL,
	[ProjectId] [int] NOT NULL,
	[AssigneeId] [int] NOT NULL,
	[Status] [nvarchar](50) NOT NULL,
	[DateCreation] [datetime] NOT NULL,
	[IdCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
 CONSTRAINT [PK_Task] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Teams]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Teams](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[TeamName] [nvarchar](50) NOT NULL,
	[ProjectId] [int] NOT NULL,
	[DateCreation] [datetime] NOT NULL,
	[IdCreator] [int] NOT NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NOT NULL,
 CONSTRAINT [PK_Team] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Users]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Users](
	[Id] [int] IDENTITY(1,1) NOT NULL,
	[UserName] [nvarchar](50) NOT NULL,
	[Password] [nvarchar](100) NOT NULL,
	[FirstName] [nvarchar](50) NOT NULL,
	[LastName] [nvarchar](50) NOT NULL,
	[DateOfCreation] [datetime] NOT NULL,
	[IdOfCreator] [int] NULL,
	[DateLastChange] [datetime] NOT NULL,
	[IdLastChange] [int] NULL,
	[IsAdmin] [bit] NULL,
 CONSTRAINT [PK_User] PRIMARY KEY CLUSTERED 
(
	[Id] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[UsersTeams]    Script Date: 7/13/2021 3:40:46 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[UsersTeams](
	[UserId] [int] NOT NULL,
	[TeamId] [int] NOT NULL,
 CONSTRAINT [PK_UsersTeams] PRIMARY KEY CLUSTERED 
(
	[UserId] ASC,
	[TeamId] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET IDENTITY_INSERT [dbo].[Logs] ON 
GO
INSERT [dbo].[Logs] ([Id], [UserId], [TimeSpent], [Date], [TaskId]) VALUES (1, 2, 3, CAST(N'2021-07-11' AS Date), 2)
GO
INSERT [dbo].[Logs] ([Id], [UserId], [TimeSpent], [Date], [TaskId]) VALUES (2, 2, 2, CAST(N'2021-07-12' AS Date), 2)
GO
INSERT [dbo].[Logs] ([Id], [UserId], [TimeSpent], [Date], [TaskId]) VALUES (3, 3, 2, CAST(N'2021-07-11' AS Date), 2)
GO
SET IDENTITY_INSERT [dbo].[Logs] OFF
GO
SET IDENTITY_INSERT [dbo].[Projects] ON 
GO
INSERT [dbo].[Projects] ([Id], [Name], [Description], [OwnerId], [DateCreation], [IdCreator], [DateLastChange], [IdLastChange]) VALUES (1, N'project1', N'project', 1, CAST(N'2021-07-12T13:45:59.357' AS DateTime), 1, CAST(N'2021-07-12T13:45:59.357' AS DateTime), 1)
GO
INSERT [dbo].[Projects] ([Id], [Name], [Description], [OwnerId], [DateCreation], [IdCreator], [DateLastChange], [IdLastChange]) VALUES (2, N'Test project', N'this is a test project', 1, CAST(N'2021-07-12T15:04:55.520' AS DateTime), 1, CAST(N'2021-07-12T16:00:22.023' AS DateTime), 1)
GO
SET IDENTITY_INSERT [dbo].[Projects] OFF
GO
SET IDENTITY_INSERT [dbo].[Tasks] ON 
GO
INSERT [dbo].[Tasks] ([Id], [Title], [Description], [ProjectId], [AssigneeId], [Status], [DateCreation], [IdCreator], [DateLastChange], [IdLastChange]) VALUES (1, N'task1', N'test task', 2, 3, N'pending', CAST(N'2021-07-12T16:31:25.117' AS DateTime), 1, CAST(N'2021-07-12T16:31:25.117' AS DateTime), 1)
GO
INSERT [dbo].[Tasks] ([Id], [Title], [Description], [ProjectId], [AssigneeId], [Status], [DateCreation], [IdCreator], [DateLastChange], [IdLastChange]) VALUES (2, N'Test task', N'This is a test task', 2, 2, N'in progress', CAST(N'2021-07-13T09:44:57.390' AS DateTime), 1, CAST(N'2021-07-13T10:26:36.130' AS DateTime), 1)
GO
SET IDENTITY_INSERT [dbo].[Tasks] OFF
GO
SET IDENTITY_INSERT [dbo].[Teams] ON 
GO
INSERT [dbo].[Teams] ([Id], [TeamName], [ProjectId], [DateCreation], [IdCreator], [DateLastChange], [IdLastChange]) VALUES (1, N'team2', 1, CAST(N'2021-07-12T13:48:03.700' AS DateTime), 1, CAST(N'2021-07-12T13:55:17.133' AS DateTime), 1)
GO
SET IDENTITY_INSERT [dbo].[Teams] OFF
GO
SET IDENTITY_INSERT [dbo].[Users] ON 
GO
INSERT [dbo].[Users] ([Id], [UserName], [Password], [FirstName], [LastName], [DateOfCreation], [IdOfCreator], [DateLastChange], [IdLastChange], [IsAdmin]) VALUES (1, N'admin', N'adminpass', N'admin', N'admin', CAST(N'2021-07-07T10:45:32.770' AS DateTime), 1, CAST(N'2021-07-07T10:45:32.770' AS DateTime), 1, 1)
GO
INSERT [dbo].[Users] ([Id], [UserName], [Password], [FirstName], [LastName], [DateOfCreation], [IdOfCreator], [DateLastChange], [IdLastChange], [IsAdmin]) VALUES (2, N'user1', N'password1', N'user', N'user', CAST(N'2021-07-08T10:35:47.820' AS DateTime), 1, CAST(N'2021-07-08T14:11:39.017' AS DateTime), 1, 0)
GO
INSERT [dbo].[Users] ([Id], [UserName], [Password], [FirstName], [LastName], [DateOfCreation], [IdOfCreator], [DateLastChange], [IdLastChange], [IsAdmin]) VALUES (3, N'user2', N'password2', N'user2', N'user2', CAST(N'2021-07-08T10:42:27.957' AS DateTime), 1, CAST(N'2021-07-08T14:12:33.937' AS DateTime), 1, 0)
GO
INSERT [dbo].[Users] ([Id], [UserName], [Password], [FirstName], [LastName], [DateOfCreation], [IdOfCreator], [DateLastChange], [IdLastChange], [IsAdmin]) VALUES (4, N'user3', N'password3', N'user3', N'user3', CAST(N'2021-07-08T10:45:53.673' AS DateTime), 1, CAST(N'2021-07-08T10:45:53.673' AS DateTime), 1, 0)
GO
INSERT [dbo].[Users] ([Id], [UserName], [Password], [FirstName], [LastName], [DateOfCreation], [IdOfCreator], [DateLastChange], [IdLastChange], [IsAdmin]) VALUES (1003, N'userIdk', N'userIdk123', N'user', N'idk', CAST(N'2021-07-13T11:59:53.390' AS DateTime), 1, CAST(N'2021-07-13T11:59:53.390' AS DateTime), 1, 0)
GO
SET IDENTITY_INSERT [dbo].[Users] OFF
GO
ALTER TABLE [dbo].[Logs] ADD  CONSTRAINT [DF_Logs_Date]  DEFAULT (getdate()) FOR [Date]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_DateCreation]  DEFAULT (getdate()) FOR [DateCreation]
GO
ALTER TABLE [dbo].[Projects] ADD  CONSTRAINT [DF_Projects_DateLastChange]  DEFAULT (getdate()) FOR [DateLastChange]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_DateCreation]  DEFAULT (getdate()) FOR [DateCreation]
GO
ALTER TABLE [dbo].[Tasks] ADD  CONSTRAINT [DF_Tasks_DateLastChange]  DEFAULT (getdate()) FOR [DateLastChange]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_DateCreation]  DEFAULT (getdate()) FOR [DateCreation]
GO
ALTER TABLE [dbo].[Teams] ADD  CONSTRAINT [DF_Teams_DateLastChange]  DEFAULT (getdate()) FOR [DateLastChange]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_DateOfCreation_1]  DEFAULT (getdate()) FOR [DateOfCreation]
GO
ALTER TABLE [dbo].[Users] ADD  CONSTRAINT [DF_Users_DateLastChange_1]  DEFAULT (getdate()) FOR [DateLastChange]
GO
ALTER TABLE [dbo].[Logs]  WITH CHECK ADD  CONSTRAINT [FK_Log_Task] FOREIGN KEY([TaskId])
REFERENCES [dbo].[Tasks] ([Id])
GO
ALTER TABLE [dbo].[Logs] CHECK CONSTRAINT [FK_Log_Task]
GO
ALTER TABLE [dbo].[Logs]  WITH CHECK ADD  CONSTRAINT [FK_Logs_Users1] FOREIGN KEY([UserId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Logs] CHECK CONSTRAINT [FK_Logs_Users1]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsIdCreator_UsersId] FOREIGN KEY([IdCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_ProjectsIdCreator_UsersId]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsIdLastChange_UsersId] FOREIGN KEY([IdLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_ProjectsIdLastChange_UsersId]
GO
ALTER TABLE [dbo].[Projects]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsOwnerId_UsersId] FOREIGN KEY([OwnerId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Projects] CHECK CONSTRAINT [FK_ProjectsOwnerId_UsersId]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Project] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Project]
GO
ALTER TABLE [dbo].[ProjectsTeams]  WITH CHECK ADD  CONSTRAINT [FK_ProjectsTeams_Team] FOREIGN KEY([TeamsId])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[ProjectsTeams] CHECK CONSTRAINT [FK_ProjectsTeams_Team]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [FK_Tasks_Projects] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [FK_Tasks_Projects]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Projects] FOREIGN KEY([ProjectId])
REFERENCES [dbo].[Projects] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Projects]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_Teams_Users] FOREIGN KEY([IdCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_Teams_Users]
GO
ALTER TABLE [dbo].[Teams]  WITH CHECK ADD  CONSTRAINT [FK_TeamsIdLastChange_UsersId] FOREIGN KEY([IdLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Teams] CHECK CONSTRAINT [FK_TeamsIdLastChange_UsersId]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_IdLastChange_Id] FOREIGN KEY([IdLastChange])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_IdLastChange_Id]
GO
ALTER TABLE [dbo].[Users]  WITH CHECK ADD  CONSTRAINT [FK_IdOfCreator_Id] FOREIGN KEY([IdOfCreator])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[Users] CHECK CONSTRAINT [FK_IdOfCreator_Id]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_Team] FOREIGN KEY([TeamId])
REFERENCES [dbo].[Teams] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_Team]
GO
ALTER TABLE [dbo].[UsersTeams]  WITH CHECK ADD  CONSTRAINT [FK_UsersTeams_User] FOREIGN KEY([UserId])
REFERENCES [dbo].[Users] ([Id])
GO
ALTER TABLE [dbo].[UsersTeams] CHECK CONSTRAINT [FK_UsersTeams_User]
GO
ALTER TABLE [dbo].[Tasks]  WITH CHECK ADD  CONSTRAINT [CK_Tasks_Status] CHECK  (([Status]='pending' OR [Status]='in progress' OR [Status]='complete'))
GO
ALTER TABLE [dbo].[Tasks] CHECK CONSTRAINT [CK_Tasks_Status]
GO
USE [master]
GO
ALTER DATABASE [ProjectManagement] SET  READ_WRITE 
GO
